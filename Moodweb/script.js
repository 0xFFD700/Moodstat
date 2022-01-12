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

    week()

}


function week() {
    var xValues = [];
    var yValues = [];

    for (let i = 1; i < 8; i++) {
        var x = moment().weekday(i).format('YYYY-MM-DD')
        var y = null;

        for (let j = 0; j < lines.length; j++) {

            if (lines[j][0] === x) {
                y = lines[j][2];

            }
        }

        yValues.push(y)
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