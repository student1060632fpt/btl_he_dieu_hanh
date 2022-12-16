# btl_he_dieu_hanh
Lệnh chạy project

- B1: cài tất cả package đang có trong project
```
sudo apt install
```

- B2: To start the simulation, you must compile the source code first by using  `Make all` command.
```
make all
```

- B3: How to Run the Simulation, chạy các file hiện có trong folder input, ví dụ file sched_0
```
./os sched_0
```

- để xóa file trong obj
```
make clean
```

# chia
shedule : thảo, tuấn
memory : hải, hòa

check đáp án ở nhánh dap-an


# Memory management 
The virtual memory engine sử dụng cơ chế Phân đoạn (Segmentation) với phân trang (Paging) để quản lý bộ nhớ. Theo mặc định, kích thước của RAM ảo là 1 MB, vì vậy chúng tôi phải sử dụng 20 bit để biểu thị địa chỉ của từng byte của nó. Với phân đoạn với cơ chế phân trang, chúng tôi sử dụng 5 bit đầu tiên cho chỉ mục phân đoạn, 5 bit tiếp theo cho trang chỉ mục và 10 bit cuối cùng cho phần bù. Bạn có thể muốn xem lại ghi chú bài giảng chương 8 (trang #38 - #39) để hiểu cơ chế này hoạt động như thế nào. Sau đó, bạn có thể thực hiện quá trình dịch ảo địa chỉ của một quy trình thành vật lý bằng cách hoàn thành các chức năng sau: