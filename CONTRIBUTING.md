# Contributing to CityRoute

Short rules so the two of us can work in parallel without breaking each other.

## Who owns what

| Member | Owns |
|---|---|
| Zunain | Utils (Haversine), Graph, OSM parser, MinHeap, Router (Dijkstra, A*, BFS, DFS, road closures), KDTree, Trie, MergeSort, algorithm benchmarks, routing integration |
| Member 2 | ArrayStack, LinkedStack, SinglyLinkedList, DoublyLinkedList, ArrayQueue, LinkedQueue, user accounts and roles, trip history, trip planner, menu system, README and report |

You write and test your own modules. Changing the other person's file? Tell them first.

## Daily routine

1. `git pull --rebase` before you start.
2. Work on your own branch: `feature/<module>` (example: `feature/graph-core`).
3. Make sure it compiles and your test passes before every push.
4. Push at least once a day and send a 3-line update (Done / Doing / Blocked).

## Commit messages

`type(scope): short description`

- `feat(stack): add array-based stack`
- `test(trie): add prefix tests`
- `fix(graph): handle one-way roads`
- `refactor: ...`, `docs: ...`, `build: ...`

## Pull requests

- Open a PR into `main` every 2-3 days, or when a module is finished.
- The other member reviews and approves it.
- Merge with "Create a merge commit". Do not squash, or the commit history collapses into one commit.

## Build and test

```
cmake -S . -B build
cmake --build build
cd build && ctest --output-on-failure
```

Any `tests/test_*.cpp` file is picked up automatically (MSVC users: `ctest -C Release`).

## Code style

- No comments in the code. Use clear names instead.
- Keep it simple: plain arrays instead of vector, `using namespace std;` in files that use cout or string.
- Only use these libraries: iostream, string, unordered_map (for hash maps), and fstream for files.
- Classes in PascalCase, functions and variables in camelCase.
- Data structures are templates in `include/` (header only), everything else goes in `src/`.
- One test file per module: `tests/test_<module>.cpp`.

## Repository rules

- Never commit build output (`build/`), editor folders, or files above 50 MB.
- Keep the map extract in `data/` small (a limited area only).
- Do not force push to `main`.
