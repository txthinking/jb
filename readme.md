# `jb` = `javascript` + `bash`

```
#!/usr/bin/env jb

$`ls -l`

var output = $1`whoami`
$(`echo ${output}`)
```

Bash is great, but when it comes to writing more complex scripts, many people prefer a more convenient programming language. JavaScript is a perfect choice. The jb provides useful wrappers. The jb is a [bun](https://github.com/oven-sh/bun) port of [zx](https://github.com/google/zx), the advantage is that you don't need to install node, and **jb is just a standalone binary**.

## Install

jb is just a standalone binary, so you can [download](https://github.com/txthinking/jb/releases) and put it in your PATH. Or install it via [nami](https://github.com/txthinking/nami)

```
nami install jb
```

## Documentation

Just write your scripts in a file with an `.js`

Add the following shebang to the beginning of your `jb` scripts:

```bash
#!/usr/bin/env jb
```

Now you will be able to run your script like so:

```bash
chmod +x ./script.js
./script.js
```

Or via the `jb` executable:

```bash
jb ./script.js
```

Or executes remote script

```bash
jb https://www.txthinking.com/script.js
```

All functions (`$`, `cd`, `fetch`, etc) are available straight away without any imports.

### ``$`command` ``

Executes a given command, keep the default behavior of stdout and stderr like bash

```js
$`ls -l`
```

Or put a variable in command

```js
var name = 'hello'
$(`mkdir ${name}`)
```

You can pass an array of arguments if needed:

```js
var flags = [
  '-l',
  '-h',
]
$(`ls ${flags.join(' ')}`)
```

If the executed program failed, stderr will be thrown.

```js
try {
  $`brook unknownsubcommand`
} catch (e) {
  console.log(`Error: ${e}`)
}
```

### ``$1`command` ``

Same as ``$`command` ``, but will return stdout and trim space, as you know, 1 is STDOUT

```js
var count = $1`ls -l | wc -l`
$(`echo ${count}`)
```

## Sync Functions

### `env()`

Set env

```js
env({
    HELLO: "JB",
})
$`echo $HELLO` // => JB
```

### `cd()`

Changes the current working directory.

```js
cd('/tmp')
$`pwd` // => /tmp
```

### `question()`

```js
var name = question('What is your name? ')
```

### `confirm()`

```js
var ok = confirm('Do you really want to leave?');
```

### `sleep()`

```js
sleep(1000)
```

### `now()`

Current unix timestamp

```js
var t = now()
```

### `echo()`

A `console.log()` alternative

```js
echo('hello')
```

### `which()`

File path or null

```js
var bin = which('brook')
```
### `cp()`

Copy file or http file from zip/tar.gz/tar.xz to local

```
cp('https://github.com/txthinking/brook/releases/latest/download/brook_darwin_arm64', '/tmp/brook');
```

Copy file from zip
```
7z l ~/Downloads/bun-darwin-aarch64.zip
```
```
   Date      Time    Attr         Size   Compressed  Name
------------------- ----- ------------ ------------  ------------------------
2023-06-03 15:54:41 D....            0            0  bun-darwin-aarch64
2023-06-03 15:54:41 .....     46584592     16787941  bun-darwin-aarch64/bun
------------------- ----- ------------ ------------  ------------------------
2023-06-03 15:54:41           46584592     16787941  1 files, 1 folders
```

```js
cp('$HOME/Downloads/bun-darwin-aarch64.zip', 'bun-darwin-aarch64/bun', '/tmp/bun');
```

Copy multiple files from tar.gz
```
tar ztf ~/Downloads/cowsay_2.0.4_macOS_arm64.tar.gz
```
```
LICENSE
doc/cowsay.1
cowsay
cowthink
```
```js
cp('$HOME/Downloads/cowsay_2.0.4_macOS_arm64.tar.gz', {
    'cowsay': '/tmp/cowsay',
    'cowthink': '/tmp/cowthink',
});
```
Copy multiple files from tar.xz
```
tar Jtf ~/Downloads/shadowsocks-v1.15.3.aarch64-apple-darwin.tar.xz
```
```
sslocal
ssserver
ssurl
ssmanager
ssservice
```
```js
cp('https://github.com/shadowsocks/shadowsocks-rust/releases/latest/download/shadowsocks-v1.15.3.aarch64-apple-darwin.tar.xz', {
    'sslocal': '/tmp/sslocal',
    'ssserver': '/tmp/ssserver',
});
```

## Async Functions

### `fetch()`

A wrapper around the [fetch](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API) package.

```js
var res = await fetch('https://www.txthinking.com')
```

### `readurl()`

Read the body from http url

```js
var str = await readurl('https://www.txthinking.com')
```

### `readfile()`

Read the text from local file

```js
var str = await readfile('path/to/file.txt')
```

### `writefile()`

Write text to local file

```js
await writefile('path/to/file.txt', 'some text')
```

### `appendfile()`

Append text to local file

```js
await appendfile('path/to/file.txt', 'some text')
```

### `stdin()`

Returns the stdin as a string.

```js
var content = await stdin()
```

### `retry()`

Will return after the first successful attempt, or will throw after specifies attempts count.

```js
var s = await retry(() => $1`curl https://www.txthinking.com`)

// delay 1s
var s = await retry(() => $1`curl https://www.txthinking.com`, 1000)

// delay 1s and max 3 times
var s = await retry(() => $1`curl https://www.txthinking.com`, 1000, 3)
```

### All [bun](https://github.com/oven-sh/bun) api without `package.json` and zero-configuration

```js
import os from 'node:os';

echo(os.homedir());
```

### Executing commands on remote hosts

The `jb` uses [sshexec](https://github.com/txthinking/sshexec) to execute commands on remote hosts.

```js
$`sshexec -s 1.2.3.4:22 -u user -p pass -c 'ls -l'`
```
Download file from remote

```js
$`sshexec -s 1.2.3.4:22 -u user -p pass --download /server/path/to/file --to /local/path/to/file`
```
Upload file to remote

```js
$`sshexec -s 1.2.3.4:22 -u user -k path/to/private/key --upload /local/path/to/file --to /server/path/to/file`
```

## License

[MIT](LICENSE)

