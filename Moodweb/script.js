var lines = [];

$.ajax({
    type: "GET",
    url: "test.csv",
    dataType: "text",
    success: function(data) {
        processData(data)
    }
});

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


    if (window.location.href.includes("week")) {
        week()
        console.log("ding")
    } else if (window.location.href.includes("month")) {
        //month()
    } else if (window.location.href.includes("year")) {
        year()
    } else {
        moodIndex()
    }


}

function moodIndex() {

    var moodTarget = document.getElementById('moodvalue')
    var timeTarget = document.getElementById('timevalue')

    timeTarget.innerText = lines.at(-1)[0] + " at " + lines.at(-1)[1];

    switch (lines.at(-1)[2]) {
        case "0":
            moodTarget.innerText = "👍";
            break
        case "1":
            moodTarget.innerText = "🖕";
            break
        case "2":
            moodTarget.innerText = "👎";
            break
    }
}

function week() {
    var xValues = [];
    var yValues = [];

    for (let i = 1; i < 8; i++) {
        var x = moment().weekday(i).format('YYYY-MM-DD')
        var y = 0
        var yCount = 0;

        for (let j = 0; j < lines.length; j++) {

            if (lines[j][0] === x) {
                y += parseInt(lines[j][2])
                yCount++
                console.log(yCount)
                console.log(y)

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

function year() {
    var xValues = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    var yValues = []

    for (let i = 1; i < 13; i++) {
        var x = moment().month(i).format('YYYY-MM-DD')
        var y = null
        var yCount = 0;

        for (let j = 0; j < lines.length; j++) {

            if (lines[j][0] === x) {
                y += lines[j][2]
                yCount++

            }
        }

        if (yCount == 0) {
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