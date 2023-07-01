const chartTemp = new Chart("chartTemp", {
  type: "line",
  data: {
    datasets: [
      {
        label: "Nhiệt độ",
        fill: false,
        borderColor: "rgb(75, 192, 192)",
        tension: 0.1,
      },
    ],
  },
  options: {
    scales: {
      yAxes: [{ ticks: { min: 20, max: 40 } }],
    },
  },
});

function addData(chart, label, data) {
  chart.data.labels.push(label);
  chart.data.datasets.forEach((dataset) => {
    dataset.data.push(data);
  });
  chart.update();
}

function removeData(chart) {
  chart.data.labels.pop();
  chart.data.datasets.forEach((dataset) => {
      dataset.data.pop();
  });
  chart.update();
}