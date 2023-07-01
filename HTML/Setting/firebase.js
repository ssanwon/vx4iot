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
var tempDelta1 = 0;
var tempAlarm = 0;
var tempDelta2 = 0;
var time = 0;

const ref_temp = ref(db, 'Setting/temp');
onValue(ref_temp, (snapshot) => {
    temp = snapshot.val();
    document.getElementById('temp').value = temp;
});

const ref_tempDelta1 = ref(db, 'Setting/tempDelta1');
onValue(ref_tempDelta1, (snapshot) => {
    tempDelta1 = snapshot.val();
    document.getElementById('tempDelta1').value = tempDelta1;
});

const ref_tempAlarm = ref(db, 'Setting/tempAlarm');
onValue(ref_tempAlarm, (snapshot) => {
    tempAlarm = snapshot.val();
    document.getElementById('tempAlarm').value = tempAlarm;
});

const ref_tempDelta2 = ref(db, 'Setting/tempDelta2');
onValue(ref_tempDelta2, (snapshot) => {
    tempDelta2 = snapshot.val();
    document.getElementById('tempDelta2').value = tempDelta2;
});

const ref_time = ref(db, 'Setting/time');
onValue(ref_time, (snapshot) => {
    time = snapshot.val();
    document.getElementById('time').value = time;
});


const bt_update = document.getElementById('bt_update');

bt_update.addEventListener('click',(e) => {
    update(ref(db, 'Setting'), {
        temp: document.getElementById('temp').value,
        tempDelta1: document.getElementById('tempDelta1').value,
        tempAlarm: document.getElementById('tempAlarm').value,
        tempDelta2: document.getElementById('tempDelta2').value,
        time: document.getElementById('time').value,
    });
});