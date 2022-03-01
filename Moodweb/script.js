var lines = [];

// Get Data 
$.ajax({
    type: "GET",
    url: moment().year() + ".csv",
    dataType: "text",
    success: function(data) {
        processData(data)
    }
});

// Converts CSV in Array
function processData(allText) {
    var allTextLines = allText.split(/\r\n|\n/);
    var headers = allTextLines[0].split(',');

    for (var i = 1; i < allTextLines.length; i++) {
        var data = allTextLines[i].split(',');
        if (data.length == headers.length) {
            var tarr = [];
            for (var j = 0; j < headers.length; j++) {
                tarr.push(data[j]);
            }
            lines.push(tarr);
        }
    }

    // Calls function depending on HTML site
    if (window.location.href.includes("week")) {
        week()
        console.log("ding")
    } else if (window.location.href.includes("month")) {
        month()
    } else if (window.location.href.includes("year")) {
        year()
    } else {
        moodIndex()
    }
}

// index.hmtl
function moodIndex() {

    var moodTarget = document.getElementById('moodvalue')
    var timeTarget = document.getElementById('timevalue')

    timeTarget.innerText = lines[lines.length - 1][0] + " at " + lines[lines.length - 1][1];

    switch (lines[lines.length - 1][2]) {
        case "0":
            moodTarget.innerText = "👎";
            break
        case "1":
            moodTarget.innerText = "🖕";
            break
        case "2":
            moodTarget.innerText = "👍";
            break
    }
}

// month.hmtl
function month() {
    var xValues = [];
    var yValues = [];

    for (let i = 1; i <= moment().daysInMonth(); i++) {
        var x = moment().format('YYYY-MM-').concat(i > 9 ? "" + i : "0" + i)
        var y = 0
        var yCount = 0;

        for (let j = 0; j < lines.length; j++) {
            if (lines[j][0] === x) {
                y += parseInt(lines[j][2])
                yCount++
            }
        }

        if (yCount == 0) {
            yValues.push(null)
        } else if (yCount == 1) {
            yValues.push(y)
        } else {
            yValues.push(y / yCount)
        }
        xValues.push(x)
    }

    new Chart("myChart", {
        type: "line",
        data: {
            labels: xValues,
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgba(0,0,255,0.1)",
                data: yValues,
                spanGaps: true
            }]
        },
        options: {
            legend: {
                display: false
            },
            scales: {
                yAxes: [{
                    ticks: {
                        min: 0,
                        max: 2
                    }
                }],
            }
        }
    });
}

// week.hmtl
function week() {
    var xValues = [];
    var yValues = [];

    for (let i = 0; i < 7; i++) {
        var x = moment().weekday(i).format('YYYY-MM-DD')
        var y = 0
        var yCount = 0;

        for (let j = 0; j < lines.length; j++) {
            if (lines[j][0] === x) {
                y += parseInt(lines[j][2])
                yCount++
            }
        }

        if (yCount == 0) {
            yValues.push(null)
        } else if (yCount == 1) {
            yValues.push(y)
        } else {
            yValues.push(y / yCount)
        }
        xValues.push(x)
    }

    new Chart("myChart", {
        type: "line",
        data: {
            labels: xValues,
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgba(0,0,255,0.1)",
                data: yValues,
                spanGaps: true
            }]
        },
        options: {
            legend: {
                display: false
            },
            scales: {
                yAxes: [{
                    ticks: {
                        min: 0,
                        max: 2
                    }
                }],
            }
        }
    });
}

// year.hmtl
function year() {
    var xValues = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    var yValues = []

    for (let i = 1; i < 13; i++) {
        var month = i > 9 ? "" + i : "0" + i;
        var y = 0
        var yCount = 0;

        for (let j = 0; j < lines.length; j++) {
            if (lines[j][0].substring(5, 7) === month) {
                y += parseInt(lines[j][2])
                yCount++
            }
        }

        if (yCount == 0) {
            yValues.push(null)
        } else if (yCount == 1) {
            yValues.push(y)
        } else {
            yValues.push(y / yCount)
        }
    }

    new Chart("myChart", {
        type: "line",
        data: {
            labels: xValues,
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgba(0,0,255,0.1)",
                data: yValues,
                spanGaps: true
            }]
        },
        options: {
            legend: {
                display: false
            },
            scales: {
                yAxes: [{
                    ticks: {
                        min: 0,
                        max: 2
                    }
                }],
            }
        }
    });
}