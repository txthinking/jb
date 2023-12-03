// TODO embed runtime?
import jb_os from 'node:os';
import jb_path from 'node:path';
import jb_fs from 'node:fs';

var jb_cwd = process.cwd();
global.echo = console.log;
global.question = prompt;
global.sleep = Bun.sleepSync;
global.which = Bun.which;
global.exit = process.exit;
global.now = () => {
    return parseInt(Date.now() / 1000);
};
global.env = (k, v) => {
    process.env[k] = v
};
global.cd = (dir) => {
    if (jb_path.isAbsolute(dir)) {
        jb_cwd = dir;
        return;
    }
    jb_cwd = jb_path.join(jb_cwd, dir);
};
global.$ = (first) => {
    var cmd = first instanceof Array ? first[0] : first;
    echo(cmd);
    var p = Bun.spawnSync(["sh", "-c", cmd], {
        cwd: jb_cwd,
        stdin: null,
        stdout: Bun.stdout,
        stderr: Bun.stderr,
    });
    if (!p.success) {
        throw `command ${cmd} failed`;
    }
};
global.$1 = (first) => {
    var cmd = first instanceof Array ? first[0] : first;
    var p = Bun.spawnSync(["sh", "-c", cmd], {
        cwd: jb_cwd,
        stdin: null,
        stdout: 'pipe',
        stderr: Bun.stderr,
    });
    if (!p.success) {
        throw `command ${cmd} failed`;
    }
    if (!p.stdout) {
        return null;
    }
    return p.stdout.toString().trim();
};
global.cp = (from, a, b) => {
    var out = "";
    if (from.endsWith(".zip")) {
        out = "_.zip";
        if (!which("7z")) {
            throw 'need 7z, recommend $ nami install 7z';
        }
    }
    if (from.endsWith(".tar.gz") || from.endsWith(".tgz")) {
        out = "_.tgz";
    }
    if (from.endsWith(".tar.xz") || from.endsWith(".txz")) {
        out = "_.txz";
    }
    if (!out) {
        $(`curl -L --progress-bar "${from}" -o "${a}"`);
        return;
    }
    if (from.startsWith("https://") || from.startsWith("http://")) {
        $(`curl -L --progress-bar "${from}" -o /tmp/${out}`);
    } else {
        $(`cp "${from}" /tmp/${out}`);
    }
    $(`rm -rf /tmp/_`)
    $(`mkdir /tmp/_`)
    if (out.endsWith('.zip')) {
        $(`7z x /tmp/${out} -o/tmp/_`)
    }
    if (out.endsWith('.tgz')) {
        $(`tar zxvf /tmp/${out} -C /tmp/_`)
    }
    if (out.endsWith('.txz')) {
        $(`tar Jxvf /tmp/${out} -C /tmp/_`)
    }
    if (typeof a == 'string') {
        $(`cp "/tmp/_/${a}" "${b}"`)
        return
    }
    Object.keys(a).forEach(v => {
        $(`cp "/tmp/_/${v}" "${a[v]}"`)
    });
};
global.exists_file = (file) => {
    return jb_fs.existsSync(file);
};
global.read_file = (file) => {
    return jb_fs.readFileSync(file, { encoding: "utf8" });
};
global.write_file = (file, text) => {
    return jb_fs.writeFileSync(file, text, { encoding: "utf8" });
};
global.append_file = (file, text) => {
    return jb_fs.writeFileSync(file, text, { encoding: "utf8", flag: 'a' });
};

// async

global.read_url = async (url) => {
    var res = await fetch(url);
    if (!res.ok) {
        throw res.status + ": " + (await res.text());
    }
    return await res.text();
};
global.stdin = async () => {
    var reader = (await Bun.stdin.stream()).getReader();
    var l = [];
    for (; true;) {
        var { done, value } = await reader.read();
        if (value) {
            l.push(value);
        }
        if (done) {
            break;
        }
    }
    var b = new Uint8Array(l.reduce((v, a) => a.length + v, 0));
    var i = 0;
    l.forEach(v => {
        b.set(v, i);
        i += v.length;
    });
    return new TextDecoder().decode(b);
};
global.retry = async (f, delay, times) => {
    var i = 0;
    for (; true; i++) {
        try {
            return await f();
        } catch (e) {
            if (i < times) {
                if (delay) {
                    sleep(delay);
                }
                continue;
            }
            throw e;
        }
    }
};

// deprecated

global.exists = (file) => {
    return jb_fs.existsSync(file);
};
global.readfile = async (file) => {
    return await Bun.file(file).text();
};
global.writefile = async (file, text) => {
    return await Bun.write(file, text);
};
global.appendfile = async (file, text) => {
    return await Bun.write(file, (await readfile(file)) + text);
};
global.readurl = async (url) => {
    var res = await fetch(url);
    if (!res.ok) {
        throw res.status + ": " + (await res.text());
    }
    return await res.text();
};

// for https://github.com/txthinking/nami

global.nami = {
    os: jb_os.platform(),
    arch: jb_os.arch() == 'x64' ? 'amd64' : jb_os.arch(),
    home_dir: jb_os.homedir(),
    bin_dir: jb_path.join(jb_os.homedir(), '.nami', 'bin'),
    cache_dir: jb_path.join(jb_os.homedir(), '.nami', 'cache'),
    copied_dir: jb_path.join(jb_os.homedir(), '.nami', 'copied'),
    tmp_dir: jb_path.join(jb_os.homedir(), '.nami', 'tmp'),
};

