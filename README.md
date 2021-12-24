# CLI Clipboard Manager

Github personal token을 저장하는 용도로 만듦. 수정이나 기능 추가 필요

## Install
```bash
# install
git clone https://github.com/ints81/cli_clipboard_manager.git
cd cli_clipboard_manager
git submodule update --init --recursive

# buil현
mkdir -p build && cd build
cmake .. && cmake --build .
```

## Change Log
- 2021-12-25 Repository 생성, 간단한 get, set, list 기능 구현