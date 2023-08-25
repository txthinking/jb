console.log(
  undefined,
  null,
  true,
  false,
  0,
  1,
  Math.PI,
  -Math.E,
  NaN,
  Infinity,
  -Infinity,
  BigInt(0),
  BigInt(1),
  BigInt("10000000000000"),
  BigInt("-10000000000000"),
  "",
  " ",
  "Hello",
  "Hello World",
  [],
  [1, 2, 3],
  ["a", 1, null, undefined],
  [1, [2, [3, [4, [5, [6, [7, [8, [9, [10]]]]]]]]]],
  [[[[[]]]]],
  {},
  { a: 1 },
  { a: 1, b: 2, c: 3 },
  { a: { b: { c: { d: { e: { f: { g: { h: { i: { j: 10 } } } } } } } } } },
  function () {},
  function namedFunction() {},
  class {},
  class namedClass {},
  class namedClass {
    a() {}
    b = 1;
    c = [
      null,
      undefined,
      "a",
      {
        a: 1,
        b: 2,
        c: 3,
      },
    ];
  },
  new Date(0),
  new Date(NaN),
  new RegExp(),
  new RegExp("abc"),
  new RegExp("abc", "g"),
  /abc/,
  new Set(),
  new Set([1, 2, 3]),
  new WeakSet(),
  new WeakSet([{ a: 1 }, { b: 2 }, { c: 3 }]),
  new Map(),
  new Map([
    ["a", 1],
    ["b", 2],
    ["c", 3],
  ]),
  new WeakMap(),
  new WeakMap([
    [{ a: 1 }, 1],
    [{ b: 2 }, 2],
    [{ c: 3 }, 3],
  ]),
  Symbol(),
  Symbol("namedSymbol"),
  new Error(),
  new TypeError("This is a TypeError"),
  //"a".repeat(10000),
  //["a"].fill("a", 0, 10000),
  new Headers(),
  new Headers({
    a: "1",
    b: "2",
  }),
  new Request("https://example.com/"),
  new Request("https://example.com/", {
    method: "POST",
    headers: {
      a: "1",
      b: "2",
    },
    body: '{"example":true}',
  }),
  new Response(),
  new Response('{"example":true}', {
    status: 200,
    statusText: "OK",
    headers: {
      a: "1",
      b: "2",
    },
  }),
);
