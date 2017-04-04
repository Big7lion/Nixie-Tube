var dom = document.getElementById('clock');
var ctx = dom.getContext('2d');
var width = ctx.canvas.width;
var height = ctx.canvas.height;
var r = width / 2;
var rem = width / 200;

function drawBackground() {
    ctx.save();
    ctx.translate(r, r);
    ctx.beginPath();
    ctx.lineWidth = rem * 10;
    ctx.arc(0, 0, r - ctx.lineWidth / 2, 0, 2 * Math.PI, false);
    ctx.stroke();

    var hourNumber = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2];
    hourNumber.forEach(function(number, i) {
        var rad = 2 * Math.PI / 12 * i;
        var x = Math.cos(rad) * (r - 30 * rem);
        var y = Math.sin(rad) * (r - 30 * rem);
        ctx.font = 18 * rem + 'px Arial';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText(number, x, y);
    });

    for (var i = 0; i < 60; i++) {
        var rad = 2 * Math.PI / 60 * i;
        var x = Math.cos(rad) * (r - 18 * rem);
        var y = Math.sin(rad) * (r - 18 * rem);
        ctx.beginPath();
        if (i % 5 === 0) {
            ctx.fillStyle = '#032';
            ctx.arc(x, y, 2 * rem, 0, 2 * Math.PI, false);
        } else {
            ctx.fillStyle = '#ccc';
            ctx.arc(x, y, 2 * rem, 0, 2 * Math.PI, false);
        }
        ctx.fill();
    }
}

function drawHour(hour, minute) {
    ctx.save();
    ctx.beginPath();
    var rad = 2 * Math.PI / 12 * hour;
    ctx.rotate(rad + 2 * Math.PI / 3600 * minute);
    ctx.lineCap = 'round';
    ctx.lineWidth = 6 * rem;
    ctx.moveTo(0, 10);
    ctx.lineTo(0, -r / 2);
    ctx.stroke();
    ctx.restore();
}

function drawMinutes(minutes, second) {
    ctx.save();
    ctx.beginPath();
    var rad = 2 * Math.PI / 60 * minutes;
    ctx.rotate(rad + 2 * Math.PI / 3600 * second);
    ctx.lineCap = 'round';
    ctx.lineWidth = 3 * rem;
    ctx.moveTo(0, 10 * rem);
    ctx.lineTo(0, -r + 30 * rem);
    ctx.stroke();
    ctx.restore();
}

function drawSeconds(second) {
    ctx.save();
    ctx.beginPath();
    ctx.fillStyle = '#A80024';
    ctx.rotate(2 * Math.PI / 60 * second);
    ctx.moveTo(-2, 20);
    ctx.lineTo(2, 20);
    ctx.lineTo(1, -r + 18 * rem);
    ctx.lineTo(-1, -r + 18 * rem);
    ctx.fill();
    ctx.restore();
}

function drawDot() {
    ctx.beginPath();
    ctx.fillStyle = '#C4D1B4';
    ctx.arc(0, 0, 4 * rem, 0, 2 * Math.PI, false);
    ctx.fill();
}

function draw() {
    var date_time = new Date();
    ctx.clearRect(0, 0, width, height);
    drawBackground();
    drawHour(date_time.getHours(), date_time.getMinutes());
    drawMinutes(date_time.getMinutes(), date_time.getSeconds());
    drawSeconds(date_time.getSeconds());
    drawDot();
    ctx.restore();
}


draw();
setInterval(draw, 1000);