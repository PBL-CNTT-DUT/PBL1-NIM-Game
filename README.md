> **PBL1 - Project-Based Learning 1**
> Đại học Bách khoa - Đại học Đà Nẵng (DUT)

Trò chơi NIM cổ điển được xây dựng bằng **C++** với giao diện đồ họa sử dụng thư viện **Raylib**.

---

## Giới thiệu

NIM là trò chơi chiến thuật toán học cổ điển:
- Có nhiều **đống đá** (piles) trên bàn chơi
- Hai người chơi thay phiên nhau **nhặt đá** từ một đống bất kỳ
- Người nhặt viên đá **cuối cùng** sẽ **thua** (hoặc thắng, tùy luật chơi)

## Tính năng

- **2 chế độ chơi**: Người vs Người (PvP), Người vs AI (PvAI)
- **AI với 5 mức độ khó**: Very Easy → Easy → Medium → Hard → Very Hard
- **Tùy chỉnh luật chơi**:
  - Luật người lấy cuối thua / thắng
  - Giới hạn số đá được lấy mỗi lượt
  - Tùy chỉnh số đống
- **Giao diện đồ họa** với Raylib (1280x720)
  - Đám mây tương tác: hover theo vùng bốc (từ đầu đến vị trí chọn)
  - Animation đám mây bay khi bốc
- **Nhạc nền & hiệu ứng âm thanh**
  - Nút bật/tắt Sound và Music ngay trong màn chơi
- **Hệ thống gợi ý nước đi** (Hint) cho người chơi
- **Hệ thống màn hình đầy đủ**:
  - Main Menu, Match Setup, Gameplay
  - Settings, Help, Credits
- **Overlay**: Pause, Result, Confirm Exit

## Cấu trúc dự án

```
PBL1-NIM-Game/
├── assets/                  # Tài nguyên game
│   ├── fonts/               # Font chữ
│   ├── images/              # Hình ảnh
│   ├── music/               # Nhạc nền
│   └── ui/                  # UI elements (buttons, clouds...)
│
├── include/                 # Header files (.h)
│   ├── ai/                  # AI logic
│   ├── app/                 # Game application state
│   ├── assets/              # Asset loader
│   ├── audio/               # Audio manager
│   ├── common/              # Cấu trúc dữ liệu dùng chung
│   ├── config/              # Cấu hình ứng dụng
│   ├── game/                # Logic game & settings
│   ├── overlays/            # Pause, Result, Confirm Exit
│   ├── render/              # Render utilities
│   ├── screens/             # Các màn hình (menu, play, help...)
│   └── ui/                  # UI components (button, text, layout)
│
├── src/                     # Source files (.cpp)
│   ├── ai/                  # AI implementation
│   ├── app/                 # Game app logic
│   ├── assets/              # Asset loading
│   ├── audio/               # Audio management
│   ├── common/              # Utilities (array, random)
│   ├── game/                # Game logic & settings
│   ├── overlays/            # Overlay implementations
│   ├── render/              # Rendering
│   ├── screens/             # Screen implementations
│   ├── ui/                  # UI components
│   └── main.cpp             # Entry point
│
├── test/                    # Test files
└── README.md
```

## Yêu cầu hệ thống

- **Hệ điều hành**: Windows
- **Compiler**: MinGW (g++ với C++17)
- **Thư viện**: [Raylib](https://www.raylib.com/) (đã cài đặt tại `C:\raylib\raylib\src`)

## Hướng dẫn Build & Chạy

### Cách 1: Dùng VS Code Tasks (khuyến nghị)

1. Mở project bằng VS Code
2. Nhấn `Ctrl + Shift + B` để build
3. Hoặc dùng các task có sẵn:
   - **Task 01**: Compile file đang mở → `.o`
   - **Task 03**: Build toàn bộ `src/` → `nim-game.exe`
   - **Task 05**: Build & Run file đang mở

### Cách 2: Build thủ công bằng Command Line

```bash
# Bước 1: Compile tất cả source files
for /r src %f in (*.cpp) do (
    g++ -std=c++17 -g -finput-charset=UTF-8 -fexec-charset=UTF-8 ^
        -IC:\raylib\raylib\src -Iinclude -I. ^
        -c "%f" -o "build\%~nf.o"
)

# Bước 2: Link thành exe
g++ -g -static -static-libgcc -static-libstdc++ build\*.o ^
    -o nim-game.exe ^
    -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm

# Bước 3: Chạy game
nim-game.exe
```

## Cách chơi

1. Chọn **chế độ chơi** (PvP / PvAI)
2. Cấu hình **độ khó AI** và **tên người chơi**
3. Thiết lập **số đống** và **luật chơi**
4. Bắt đầu chơi:
   - Di chuột vào đám mây → toàn bộ đám mây từ đầu đến vị trí đó sáng lên (đây là số sẽ bốc)
   - Click vào đám mây để chọn số lượng muốn bốc
   - Nhấn **Enter** hoặc nút **Đồng ý** để xác nhận
5. Người lấy viên đá cuối cùng sẽ **thua** (hoặc **thắng** tùy luật đã chọn)

## Công nghệ sử dụng

| Công nghệ | Mục đích |
|-----------|----------|
| C++ (C++17) | Ngôn ngữ lập trình chính |
| Raylib | Thư viện đồ họa 2D |
| MinGW/g++ | Compiler |
| VS Code | IDE |

## Thành viên nhóm

<!-- Thêm thông tin thành viên tại đây -->

| STT | Họ và tên | Lớp | MSSV |
|-----|-----------|-----|------|
| 1 | Tạ Anh Tuấn | 25T_DT1 | |
| 2 | Tôn Nguyễn Khánh Huyền | 25T_DT4 | |

## License

Project này được thực hiện cho mục đích học tập tại **Đại học Bách khoa - Đại học Đà Nẵng**.
