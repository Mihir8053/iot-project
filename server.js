// app.js

const express = require('express');
const bodyParser = require('body-parser');
const { exec } = require('child_process');

const app = express();
const port = process.env.PORT || 3000;

app.use(bodyParser.json());

app.set('view engine', 'ejs');
app.set('views', 'views');

app.get('/', (req, res) => {
    res.send("server hit")
});

app.post('/arduino-data', (req, res) => {
    if (req) {
        console.log("DANGER!!");
        return;
    }
    const temperature = req.body.temperature;
    let turbidity = req.body.turbidity;
    // turbidity *= 1024;
    // turbidity /= 5;
    const ph = req.body.ph;
    // console.log(temperature, turbidity, ph);
    const script = `python prediction.py ${temperature} ${turbidity} ${ph}`;
    exec(script, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${error.message}`);
            res.status(500).send('Internal Server Error');
            return;
        }
        const numericValue = parseFloat(stdout.match(/\d+\.\d+/)[0]);
        res.json({ turbidity: turbidity, ph: ph, temperature: temperature, prediction: numericValue });
    });

});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})