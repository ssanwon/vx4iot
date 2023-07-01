function myFunction() {
    var dataTable = document.getElementById("data-table");
    console.log("Test");
    // Thực hiện yêu cầu HTTP
    var request = new XMLHttpRequest();
    request.open('GET', 'https://docs.google.com/spreadsheets/d/e/2PACX-1vQ1c0Pbq4i1G7f5GD20jTB37dtEDNmprwwPCYpbM-6vRh7n77UOUByZ__hqLv2NrjXycBd_2KNBEfQZ/pubhtml', true);
    
    window.location.reload = "https://docs.google.com/spreadsheets/d/e/2PACX-1vQ1c0Pbq4i1G7f5GD20jTB37dtEDNmprwwPCYpbM-6vRh7n77UOUByZ__hqLv2NrjXycBd_2KNBEfQZ/pubhtml";

    request.onload = function() {
      if (request.status >= 200 && request.status < 400) {
        // Xử lý phản hồi thành công
        var responseData = request.responseText;
        var parser = new DOMParser();
        var htmlDoc = parser.parseFromString(responseData, 'text/html');

        document.getElementById("data-table").innerHTML = "";
        
        // Lấy bảng từ tài liệu HTML
        var table = htmlDoc.getElementsByTagName('table')[0];
        
        // Tạo một bảng mới và sao chép các dòng và cột vào bảng mới
        var newTable = document.createElement('table');
        var rows = table.rows;
        for (var i = 2; i < rows.length; i++) {
          var newRow = newTable.insertRow();
          for (var j = 1; j < rows[i].cells.length; j++) {
            var newCell = newRow.insertCell();
            newCell.innerHTML = rows[i].cells[j].innerHTML;
          }
        }
  
        // Hiển thị bảng trên trang HTML
        dataTable.appendChild(newTable);
      } else {
        // Xử lý lỗi
        dataTable.innerHTML = 'Error loading table.';
      }
    };
  
    request.onerror = function() {
      // Xử lý lỗi
      dataTable.innerHTML = 'Error loading table.';
    };
  
    request.send();
}

setInterval(myFunction, 1000); // Gọi hàm myFunction mỗi giây (1000ms)

function openNewPage() {
  window.open("https://docs.google.com/spreadsheets/d/1GXbFoRcYY6_hzQMvZz4aRfPwcgMRIe7OufilQH10wyo/edit?pli=1#gid=0", "_blank");
}