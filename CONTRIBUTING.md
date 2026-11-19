# Contributing to CityRoute

Short rules so the three of us can work in parallel without breaking each other.

## Who owns what

| Member | Owns |
|---|---|
| Member 1 | OSM parser, Graph, binary cache, MinHeap, Dijkstra, A*, BFS, DFS, KD-tree, road closures, benchmarks, integration |
| Member 2 | ArrayStack, LinkedStack, ArrayQueue, LinkedQueue, SinglyLinkedList, DoublyLinkedList, user accounts and roles, trip history, admin tools |
| Member 3 | README and docs, Trie, MergeSort, TripPlanner (recursive ordering), menu system, GeoJSON export, map viewer, test scripts, report |

You write and test your own modules. Changing someone else's file? Tell them first.

## Daily routine

1. `git pull --rebase` before you start.
2. Work on **your own branch**: `feature/<module>` (example: `feature/array-stack`).
3. Make sure it **compiles and your test passes** before every push.
4. Push at least once a day and post a 3-line update in the group chat (Done / Doing / Blocked).

## Commit messages

`type(scope): short description`

- `feat(stack): add array-based stack`
- `test(trie): add prefix tests`
- `fix(graph): handle one-way roads`
- `docs: update README progress`
- `build: ...`, `refactor(...)`

## Pull requests

- Open a PR into `main` every 2-3 days (or when a module is finished).
- The reviewer reads it and approves: Member 1 reviews Member 2, Member 2 reviews Member 3, Member 3 reviews Member 1.
- Merge with **"Create a merge commit"**. Do **not** squash, or the commit history collapses into one commit.

## Build and test

```
cmake -S . -B build
cmake --build build
cd build && ctest --output-on-failure
```

Any `tests/test_*.cpp` file is picked up automatically (MSVC users: `ctest -C Release`).

## Code style

- Classes `PascalCase`, functions and variables `camelCase`, private members end with `_`.
- Every header starts with a comment: purpose, owner, and the time complexity of the main operations.
- Data structures are templates in `include/` (header only); other code goes in `src/`.
- One test file per module: `tests/test_<module>.cpp`.

## Repository rules

- Never commit build output (`build/`), editor folders, or files above 50 MB.
- Keep the map extract in `data/` small (a limited area only).
- Do not rewrite shared history (`git push --force` on `main` is not allowed).
