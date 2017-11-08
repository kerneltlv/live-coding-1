#!/usr/bin/node

const fs = require('fs');
const blessed = require('blessed');
const contrib = require('blessed-contrib');
const screen = blessed.screen();

const line = contrib.line({
    style:
        {
            line: "green",
            text: "yellow",
            baseline: "black"
        },
    xLabelPadding: 3,
    xPadding: 5,
    showLegend: true,
    wholeNumbersOnly: true
});

const data = {
    title: "Heart Rate",
    x: [0],
    y: [0]
};

screen.append(line);
line.setData([data]);

screen.key(['escape', 'q', 'C-c'], function (ch, key) {
    return process.exit(0);
});

const fd = fs.openSync('/dev/hr', 'r');

function readHeartRate() {
    fs.read(fd, Buffer.alloc(1), 0, 1, 0,
        (err, bytesRead, buffer) => {
        const heart_rate = buffer.readUInt8(0);

        data.x.push(1);
        data.y.push(heart_rate);
        line.setData([data]);

        screen.render();
    });
}

readHeartRate();
setInterval(readHeartRate, 500);