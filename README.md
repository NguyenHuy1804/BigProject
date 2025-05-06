## Thông tin sinh viên:
## Họ và tên: Nguyễn Quang Huy

## Mã sinh viên: 24022803

# Space Rush - The end of all kinds (SDL2 Version)

Đây là phiên bản game **Flappy Bỉrd giả lập** được lập trình bằng ngôn ngữ **C++** sử dụng thư viện **SDL2** và **SDL2_image**. 

Là một tựa game 2D giả lập không gian ngoài vũ trụ, lấy bối cảnh trong một tương lai xa xôi, khi trái đất không còn phù hợp để sinh tồn nữa và con người phải đi tìm những vùng đất bên ngoài trái đất để định cư. Bạn sẽ đóng vai trò là một người điều khiển con tàu vũ trụ Nasa, nhiệm vụ của bạn rất đơn giản thôi: điều khiển con tàu bay qua các chướng ngại vật và đi xa nhất có thể!

---

## [Video Demo](https://youtu.be/lBeRmOFOKyg)

## Ngưỡng điểm bảo vệ: 7.5 - 8.5
# Description:
1. Game tự viết có thuật toán nằm ngoài chương trình môn học (diểm đánh giá độ khó của thuật toán)
2. Game tự viết có đồ họa đơn giản
3. Game phát triển từ code mẫu nhưng có sự thay đổi đáng kể về nội dung và bổ sung đáng kể các tính năng mới.

# Lý do: 
## Tính năng chính

### 1. Màn hình trò chơi
- **Start Screen**: Hiển thị màn hình bắt đầu với hình nền riêng và nhạc nền.
- **Playing**: Vào game chính, điều khiển chim vượt qua các chướng ngại vật.
- **Game Over Screen**: Hiển thị kết quả và hình ảnh kết thúc game.

### 2. Điều khiển tàu
- Nhấn **phím SPACE** để chim bay lên.
- Nếu không nhấn, chim tự động rơi xuống theo trọng lực.

### 3. Tính điểm
- Mỗi lần tàu **vượt qua một cặp chướng ngại vật**, điểm số được tăng thêm 1.
- Sử dụng font chữ pixel để hiển thị điểm số trực tiếp trên màn hình.

### 4. Hệ thống chướng ngại vật 
- Các cặp chướng ngại vật trên và dưới xuất hiện ngẫu nhiên theo thời gian.
- Có kiểm tra va chạm giữa tàu và chướng ngại vật.

### 5. Hình nền di chuyển (Thuật toán đáng chú ý)
Trong game, hiệu ứng nền di chuyển (scrolling background) được thực hiện bằng cách sử dụng hai ảnh nền giống hệt nhau, đặt nối tiếp nhau theo chiều ngang. Khi game chạy, cả hai ảnh nền này sẽ liên tục trượt sang trái với tốc độ cố định, tạo cảm giác chuyển động cho người chơi giống như đang bay qua không gian.

Khi một trong hai ảnh trượt ra khỏi khung hình bên trái, nó sẽ được đặt lại phía bên phải của ảnh còn lại, để tiếp tục lặp lại chu trình. Nhờ vậy, dù thực chất chỉ có hai ảnh, người chơi vẫn cảm thấy như đang di chuyển trong một không gian nền vô hạn, không bao giờ có khoảng trống.



### Cách hoạt động

- Hai hình chữ nhật `rect1` và `rect2`, mỗi hình có kích thước bằng màn hình, lần lượt được vẽ cạnh nhau.
- Ở mỗi frame, cả hai hình chữ nhật đều dịch sang trái một lượng bằng `scrollSpeed`.
- Khi một hình ra khỏi màn hình (tọa độ x + width ≤ 0), nó sẽ được đưa về phía bên phải hình còn lại, tạo hiệu ứng **lặp vô hạn**.

### Code logic chính (`background.cpp`)

```cpp
void Background::update() {
    rect1.x -= static_cast<int>(scrollSpeed);
    rect2.x -= static_cast<int>(scrollSpeed);

    if (rect1.x + rect1.w <= 0) {
        rect1.x = rect2.x + rect2.w;
    }

    if (rect2.x + rect2.w <= 0) {
        rect2.x = rect1.x + rect1.w;
    }
}

void Background::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}
```

### 6. Âm thanh
- Có hiệu ứng âm thanh khi:
  - Tàu nhảy (flap)
  - Ghi điểm
  - Va chạm và thua
- Nhạc nền phát trong màn hình bắt đầu và màn chơi chính.

### 7. Bảng điều chỉnh âm lượng
- Nhấn **phím ESC** để bật/tắt bảng điều chỉnh âm lượng.
- Khi bảng hiện, game sẽ **tạm dừng**.
- Có thể bật/tắt nhạc nền và hiệu ứng âm thanh.

### 8. Reset trò chơi
- Sau khi thua, nhấn **bất kỳ phím nào** để chơi lại từ đầu.

### 9. Đồ họa trò chơi
---

### 🎮 Đồ họa trong Code

## Source: 
Đa phần lấy từ Google Images (promt: game 2d pixel png,...)

Game sử dụng **SDL2** và thư viện mở rộng **SDL2_image** để xử lý hiển thị hình ảnh. Các phần chính về đồ họa gồm:

- **Tải và hiển thị ảnh**:  
  - Dùng `IMG_Load()` để load ảnh từ file.  
  - Dùng `SDL_CreateTextureFromSurface()` để chuyển ảnh thành texture.  
  - Cuối cùng dùng `SDL_RenderCopy()` để vẽ ảnh lên màn hình tại vị trí được xác định bởi `SDL_Rect`.

- **Tải và hiển thị các đối tượng** (tàu, nút bấm, giao diện):  
  - Được xử lý trong các file như `Game.cpp`, `Player.cpp`, `Button.cpp`...  
  - Mỗi đối tượng đều có `loadTexture()`, `render()`, và các hàm cập nhật riêng để điều khiển vị trí và hiển thị của texture.

- **Xử lý độ phân giải & khung hình**:  
  - Game mặc định chạy ở độ phân giải 800x600.  
  - Các đối tượng được thiết kế sao cho phù hợp với tỷ lệ khung hình và không bị méo.

---


## Công nghệ sử dụng
- Ngôn ngữ: **C++**
- Thư viện: `SDL2`, `SDL2_image`, `SDL2_ttf`, `SDL2_mixer`
- Hệ điều hành phát triển: **Windows**

---

