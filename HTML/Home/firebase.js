// Them thu vien
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.18.0/firebase-app.js";
import { getDatabase, ref, set, child, get, onValue, update} from "https://www.gstatic.com/firebasejs/9.18.0/firebase-database.js";

// Cau hinh firebase
const firebaseConfig = {
    apiKey: "AIzaSyCpPpRkjFtYINVc2QJSimkbCtGIe5zQUrM",
    authDomain: "dieu-khien-nhiet-do-dixell.firebaseapp.com",
    databaseURL: "https://dieu-khien-nhiet-do-dixell-default-rtdb.firebaseio.com",
    projectId: "dieu-khien-nhiet-do-dixell",
    storageBucket: "dieu-khien-nhiet-do-dixell.appspot.com",
    messagingSenderId: "961902819526",
    appId: "1:961902819526:web:cf034f57e9acac8bfa7fc7",
    measurementId: "G-RWC55H8W3Z"
  };

// Khai bao bien  
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);
const db = getDatabase();

var temp = 0;
var timeUpdate = 0;

const ref_temp = ref(db, 'Current/temp');
onValue(ref_temp, (snapshot) => {
    temp = snapshot.val();
    document.getElementById('temperature').innerHTML = temp + "°C";
});

const ref_chart = ref(db, 'Current/time');
onValue(ref_chart, (snapshot) => {
    timeUpdate = snapshot.val();
    var time = timeUpdate.slice(0, 5);
    addData(chartTemp, time, temp);
});