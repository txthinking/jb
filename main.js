import path from "node:path";
import fs from 'node:fs';
import os from 'node:os';

// Welcome PR, translate to english if need: https://www.txthinking.com/talks/articles/coding-principle.article

var _cwd = process.cwd();
var _env = {};
global.echo = console.log;
global.question = prompt;
global.sleep = Bun.sleepSync;
global.which = Bun.which;
global.exit = process.exit;
global.now = () => {
    return parseInt(Date.now() / 1000);
};
global.env = (k, v) => {
    if(typeof k == 'string'){
        _env[k] = v;
        return
    }
    _env = {...env, ...k};
};
global.cd = (dir) => {
    if(path.isAbsolute(dir)){
        _cwd = dir;
        return;
    }
    _cwd = path.join(_cwd, dir);
};
global.$ = (first) => {
    var cmd = first instanceof Array ? first[0] : first;
    echo(cmd);
    var p = Bun.spawnSync(["sh", "-c", cmd], {
        cwd: _cwd,
        env: {...process.env, ..._env},
        stdin: null,
        stdout: Bun.stdout,
        stderr: Bun.stderr,
    });
    if(!p.success){
        throw `command ${cmd} failed`;
    }
};
global.$1 = (first) => {
    var cmd = first instanceof Array ? first[0] : first;
    echo(cmd);
    var p = Bun.spawnSync(["sh", "-c", cmd], {
        cwd: _cwd,
        env: {...process.env, ..._env},
        stdin: null,
        stdout: 'pipe',
        stderr: Bun.stderr,
    });
    if(!p.success){
        throw `command ${cmd} failed`;
        return
    }
    if(!p.stdout){
        return null;
    }
    return p.stdout.toString().trim();
};

global.readurl = async (url) => {
    var res = await fetch(url);
    if(!res.ok){
        throw res.status + ": "+ (await res.text());
    }
    return await res.text();
};
global.readfile = async (file) => {
    return await Bun.file(file).text();
};
global.writefile = async (file, text) => {
    return await Bun.write(file, text);
};
// TODO replace me
global.appendfile = async (file, text) => {
    return await Bun.write(file, (await readfile(file)) + text);
};
global.stdin = async () => {
    var reader = await Bun.stdin.stream().getReader();
    var l = [];
    for (;true;) {
        var {done, value} = await reader.read();
        if(value){
            l.push(value);
        }
        if(done){
            break;
        }
    }
    var b = new Uint8Array(l.reduce((v, a)=>a.length+v, 0));
    var i = 0;
    l.forEach(v=>{
        b.set(v, i);
        i += v.length;
    });
    return new TextDecoder().decode(b);
};
global.retry = async (f, delay, times) => {
    var i = 0;
    for(;true;i++){
        try{
            return await f();
        }catch(e){
            if(i<times){
                if(delay){
                    sleep(delay);
                }
                continue;
            }
            throw e;
        }
    }
};
global.cp = (from, a, b) => {
    var out = "";
    if(from.endsWith(".zip")){
        out = "_.zip";
        if(!which("7z")){
            throw 'need 7z, recommend $ nami install 7z';
        }
    }
    if(from.endsWith(".tar.gz") || from.endsWith(".tgz")){
        out = "_.tgz";
    }
    if(from.endsWith(".tar.xz") || from.endsWith(".txz")){
        out = "_.txz";
    }
    if(!out){
        $(`curl -L --progress-bar "${from}" -o "${a}"`);
        return;
    }
    if(from.startsWith("https://") || from.startsWith("http://")){
        $(`curl -L --progress-bar "${from}" -o /tmp/${out}`);
    }else{
        $(`cp "${from}" /tmp/${out}`);
    }
    $(`rm -rf /tmp/_`)
    $(`mkdir /tmp/_`)
    if(out.endsWith('.zip')){
        $(`7z x /tmp/${out} -o/tmp/_`)
    }
    if(out.endsWith('.tgz')){
        $(`tar zxvf /tmp/${out} -C /tmp/_`)
    }
    if(out.endsWith('.txz')){
        $(`tar Jxvf /tmp/${out} -C /tmp/_`)
    }
    if(typeof a == 'string'){
        $(`cp "/tmp/_/${a}" "${b}"`)
        return
    }
    Object.keys(a).forEach(v=>{
        $(`cp "/tmp/_/${v}" "${a[v]}"`)
    });
};

// for https://github.com/txthinking/nami
global.nami = {
    os: os.platform(),
    arch: os.arch() == 'x64' ? 'amd64' : os.arch(),
    home_dir: os.homedir(),
    bin_dir: path.join(os.homedir(), '.nami', 'bin'),
    cache_dir: path.join(os.homedir(), '.nami', 'cache'),
    copied_dir: path.join(os.homedir(), '.nami', 'copied'),
    tmp_dir: path.join(os.homedir(), '.nami', 'tmp'),
};

var main = async () => {
    var s = '$`ls -l`';
    var help = `
jb = javascript + bash

$ jb /path/to/file.js
$ jb https://example.com/file.js
$ jb '${s}'

v20230607

https://github.com/txthinking/jb
`;
    if(process.argv.length <= 2){
        echo(help);
        return;
    }
    var a = process.argv[2];
    if(a == "help" || a == "--help" || a == "-h" || a == "version" || a == "--version" || a == "-v"){
        echo(help);
        return;
    }
    if(a.startsWith('http://') || a.startsWith('https://')){
        cp(a, '/tmp/_.js');
        await import(Bun.resolveSync('/tmp/_.js', process.cwd()));
        return;
    }
    if(fs.existsSync(a)){
        await import(Bun.resolveSync(a, process.cwd()));
        return;
    }
    await writefile('/tmp/_.js', a);
    await import(Bun.resolveSync('/tmp/_.js', process.cwd()));
}

await main();
