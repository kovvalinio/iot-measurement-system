const express = require('express');
const path = require('path');
const fs = require('fs');
const { exec } = require('child_process');

const app = express();
const PORT = 8000;


const filesDirectory = path.join(__dirname, 'files');


app.use(express.static(__dirname));

app.get('/files', (req, res) => {
    fs.readdir(filesDirectory, (err, files) => {
        if (err) {
            return res.status(500).json({ message: 'Server error' });
        }
        

        const csvFiles = files.filter(file => file.endsWith('.csv')).map(file => ({
            name: file,
            path: `/files/${file}`
        }));

        res.json(csvFiles);
    });
});


app.use('/files', express.static(filesDirectory));


app.get('/start-meas', (req, res) => {
    exec('meas.exe', (err) => {
        if (err) {
            return res.status(500).json({ message: 'Could not start measurement' });
        }
        res.json({ message: 'Measurement started' });
    });
});


app.get('/stop-meas', (req, res) => {
    exec('taskkill /IM meas.exe /F', (err) => {
        if (err) {
            return res.status(500).json({ message: 'Could not stop measurement' });
        }
        res.json({ message: 'Measurement stopped' });
    });
});


app.listen(PORT, () => {
    console.log(`Server runs on port ${PORT}`);
});
