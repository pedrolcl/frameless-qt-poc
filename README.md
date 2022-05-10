# frameless-qt-poc
FramelessWindow with Qt POC

## Results

Tests built with Qt 5.15.2 and Qt 6.3.0

:heavy_check_mark: means that it is usable.

:x: means that it is not usable. See the notes.

:question: means that the results are not conclusive.

|                  | Qt5 + move window  | Qt5 + resize       | Qt6 + move window  | Qt6 + resize       |
| ---------------- | ------------------ | ------------------ | ------------------ | ------------------ |
| Windows          | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| macOS            | :heavy_check_mark: | :x:                | :heavy_check_mark: | :heavy_check_mark: |
| Linux X11        | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| Wayland          | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
