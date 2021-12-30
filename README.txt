Tác giả: Mai Nguyễn Anh Đức
Email: mnaduc@gmail.com

Chương trình được viết trên IDE: 
Microsoft Visual Studio Community 2022
Version 17.0.1

Mục đích chương trình: 	
	Xây dựng chương trình hỗ trợ thông báo cho lái xe, 
	mô tả chức năng chuyển đổi cần số và điều khiển vận tốc ô tô

Các chức năng chính:
1. Tính năng đăng nhập:
	Nhập vào một dãy dữ liệu tương ứng với mã số cá nhân (MSCN), thực hiện 
	sắp xếp, so sánh với MSCN (đã cài đặt trước) để xác thực đăng nhập.
	Cài đặt đăng nhập lần đầu nếu chưa có dữ liệu.
	Dữ liệu sẽ được đọc từ file và cập nhật vào file sau mỗi lần cài đặt và đăng nhập.
3. Đưa ra lựa chọn sử dụng cần số để thay đổi số (R: Lùi/N:Tạm dừng/D:Tiến/P:Đỗ xe) 
   và điều khiển tốc độ (tăng/giảm tốc độ, phanh)
2. Chức năng cảnh báo:
  + Cảnh báo khoảng cách an toàn ở một số dải vận tốc:
	Với 03 mức cảnh báo tốc độ <Mức1> - <Mức2> - <Mức3> (km/h)
		Nhỏ hơn <Mức1> : Cảnh báo chú ý phải giữ khoảng cách tối thiểu là 20m
		<Mức1> ~ <Mức2> : Cảnh báo chú ý phải giữ khoảng cách tối thiểu là 55m
		<Mức2> ~ <Mức3> : Cảnh báo chú ý phải giữ khoảng cách tối thiểu là 70m
		Lớn hơn <Mức3> : Cảnh báo chú ý phải giữ khoảng cách tối thiểu là 100m
	Tương tự phần đăng nhập, dữ liệu sẽ được kiểm tra trong file, và sẽ được cập nhật 
	vào file khi người dùng lựa chọn cài đặt lại
  + Cảnh báo tốc độ cao (tốc độ lớn hơn 60km/h với D hoặc 20km/h với R)
  + Cảnh báo chuyển đổi cần số
	Cảnh báo không thể về số N/P khi xe chưa dừng hẳn.
	Cảnh báo không thể chuyển đổi trực tiếp R<->D khi xe vẫn còn di chuyển
4. Tắt máy (khi lựa chọn tắt máy) và đưa ra thông báo chào tạm biệt
