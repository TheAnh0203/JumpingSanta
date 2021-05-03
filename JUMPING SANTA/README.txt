Các chức năng chính:

1. Menu có 3 button để lựa chọn chính: 
	- Start để bắt đầu vòng lặp và chạy game
	- Help để mở Instruction hướng dẫn cách chơi game
	- Exit để thoát game
	- Ngoài ra còn có button Back để quay lại menu chính khi đã đọc xong Instruction

2. Về phần hình ảnh:
	- Sử dụng file .png và bỏ qua SetColorKey
	- Background: 1 khung hình có nhà tuyết khi bắt đầu đường chạy và 1 khung hình hiển thị lặp lại khi nhân vật chạy
	- Nhân vật: 11 khung hình nhân vật, trong đó: 
			+ 10 khung hình được roll liên tục khi nhân vật trong trạng thái chạy
			+ 1 khung hình hiển thị hình ảnh nhân vật nhảy qua chướng ngại vật
	- Vật cản: 2 vật cản có tọa độ x được thay đổi một cách ngẫu nhiên
	
3. Về phần âm thanh:
	- Âm thanh Menu
	- Âm thanh khi nhân vật chạy
	- Âm thanh nhảy qua vật cản
	- Âm thanh khi nhân vật chạm vật cản (lose)

4. Trong khi chơi game:
	- Rolling background: render song song 2 background cùng thời điểm để bù vào phần background bị trôi về sau
	- Trạng thái nhảy (chuyển động đều):
		+ Nhảy lên: tọa độ y giảm dần đều
		+ Rơi xuống: tọa độ y tăng dần đều đến khi bằng y ban đầu (y ở GROUND)
	- Pause/Play Button:
		+ Pause: sử dụng để ngừng nhạc và trò chơi
		+ Play: sử dụng để phát tiếp nhạc và tiếp tục trò chơi
	- Cập nhật điểm số: Score tăng dựa trên thời gian chơi game và điểm cao (highscore) được lưu trong file .txt để hiển thị cho những lần sau
	- Va chạm: Xử lí trường hợp va chạm theo tọa độ x và theo tọa độ y	
	- Khi nhân vật va chạm với vật cản: 
		+ Hiển thị "You lose!" và hướng dẫn cách tiếp tục chơi (Space) hoặc thoát game (ESC / X)
		+ Ngừng phát nhạc và update highscore
	- Khi thoát game: dọn dẹp bộ nhớ và return 0.