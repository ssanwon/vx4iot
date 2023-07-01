// setInterval(function () {
//   addLists("On");
//   }, 3000);

// Them thu vien
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.18.0/firebase-app.js";
import {
  getDatabase,
  ref,
  set,
  child,
  get,
  onValue,
  update,
} from "https://www.gstatic.com/firebasejs/9.18.0/firebase-database.js";

// Cau hinh firebase
const firebaseConfig = {
  apiKey: "AIzaSyCpPpRkjFtYINVc2QJSimkbCtGIe5zQUrM",
  authDomain: "dieu-khien-nhiet-do-dixell.firebaseapp.com",
  databaseURL: "https://dieu-khien-nhiet-do-dixell-default-rtdb.firebaseio.com",
  projectId: "dieu-khien-nhiet-do-dixell",
  storageBucket: "dieu-khien-nhiet-do-dixell.appspot.com",
  messagingSenderId: "961902819526",
  appId: "1:961902819526:web:cf034f57e9acac8bfa7fc7",
  measurementId: "G-RWC55H8W3Z",
};

// Khai bao bien
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);
const db = getDatabase();

var timeOld = "";

const ref_chart = ref(db, "Current/time1");
onValue(ref_chart, (snapshot) => {
  console.log(snapshot.val());
  // addData(chartTemp, time, temp);

  if (snapshot.val() != timeOld) {
    timeOld = snapshot.val();

    const dataRef = ref(database, "Current/status");
    get(dataRef)
      .then((snapshot1) => {
        if (snapshot1.exists()) {
          const data = snapshot1.val();
          // Sử dụng dữ liệu tại đây
          console.log(data);
          if (data) {
            addLists("On - "+ timeOld);
          }
          else {
            addLists("Off - "+ timeOld);
          }
        } else {
          console.log("Dữ liệu không tồn tại");
        }
      })
      .catch((error) => {
        console.error("Lỗi khi đọc dữ liệu: ", error);
      });
  }
});
