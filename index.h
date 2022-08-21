const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED control</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@300&display=swap');

        :root {
            --prim_color: rgb(205, 20, 0);
            --sec_color: rgb(0, 0, 0);
        }

        body {
            background: linear-gradient(135deg, var(--prim_color), var(--sec_color));
            width: 100%;
            height: 100vh;
            margin: 0;
            font-family: 'Open Sans', sans-serif;
            color: #fefefe;
            font-size: 1.5rem;
        }

        input[type="range"] {
            accent-color: #fff;
            width: 50vw;
        }

        span {
            display: flex;
            align-items: center;
            flex-direction: column;
        }

        ul {
            list-style: none;
            padding-left: 0;
            margin: 0;
            display: flex;
            flex-direction: column;
            align-items: center;
            height: 100%;
            overflow-y: scroll;
        }

        li {
            margin: 10px 0;
            color: #c9c9c9;
            transition: all 0.2s;
        }

        button {
            font-size: inherit;
            background-color: transparent;
            color: inherit;
            border: none;
            border-bottom: 1px solid;
        }

        h3 {
            margin: 3px;
            text-align: center;
        }

        .bg {
            position: absolute;
            background: rgb(42 42 42 / 60%);
            width: 100%;
            height: 100%;
            z-index: -1;
            transition: all .2s;
        }

        .main_panel {
            display: flex;
            position: fixed;
            width: 200%;
            height: 100vh;
            flex-direction: row;
            transform: translateX(0);
            transition: all .2s;
        }

        .main_panel_animations {
            transform: translateX(-50%);
        }

        #heading {
            position: absolute;
            left: 50%;
            font-size: 2.5rem;
            transform: translateX(-50%);
            width: max-content;
            margin: 5px;
        }

        .container {
            display: grid;
            grid-template-rows: auto;
            justify-content: space-evenly;
            align-content: space-evenly;
            align-items: start;
            width: 50%;
            padding: 10% 0 15% 0;
        }

        .input_icon {
            width: 40px;
            height: 40px;
            margin-bottom: 15px;
        }

        .item-break {
            width: 60%;
            margin: 2px;
        }

        .selected_anim {
            color: #fff;
            transform: scale(1.05);
            font-weight: 700;
        }

        #color_selection_panel {
            display: none;
            flex-direction: column;
            align-items: center;
            height: 100%;
            width: 100%;
            justify-content: space-evenly;
        }

        #confirm_btn {
            background-color: transparent;
            color: inherit;
            border: none;
        }

        #colorSelection {
            display: flex;
            flex-direction: column;
            position: relative;
            align-items: center;
            width: 70vw;
        }

        #colorSelection hr{
            width: 100%;
        }

        #colorSelection div {
            position: relative;
            margin-top: 5%;
            overflow: hidden;
            width: 8em;
            height: 2em;
            border: 2px solid;
            border-radius: 4px;
            margin: 8px;
        }

        input[type='color'] {
            padding: 0;
            width: 1500px;
            height: 1500px;
            margin: -25%;
        }

        label {
            position: absolute;
            left: 20%;
            top: 10%;
        }

        #animation_section{
            min-width: 70vw;
            height: 30vh;
        }

        #navigationbar{
            position: fixed;
            bottom: 0;
            width: 95vw;
            height: 50px;
            padding: 10px;
            display: grid;
            grid-template-columns: 1fr .1fr 1fr;
            justify-items: center;
            align-items: center;
        }

        #navigationbar p {
            margin: 0;
        }

        .selectedPanel {
            font-weight: 700;
            transform: scale(1.05);
            transition: all .2s;
        }

        #topDivider{
            position: absolute;
            width: 80%;
            top: 0;
            height: 2px;
            border-width: 0;
            background: white;
        }

        #middleDivider{
            width: 2px;
            height: 90%;
            background-color: #fff;
        }
    </style>
</head>

<body>
    <div class="bg"></div>
    <h1 id="heading">LED control</h1>
    <div class="main_panel">
        <div class="container">
            <section id="colorSelection">
                <h3>Color picker</h3>
                <hr>
                <div>
                    <label for="prim_c">Prim. color</label>
                    <input type="color" oninput="changeColorInput_BGColor(this)" onchange="setColor('prim', this.value)" id="prim_c" value="#CD1400">
                </div>
                <div>
                    <label for="sec_c">Sec. color</label>
                    <input  type="color" onchange="setColor('sec', this.value)" id="sec_c">
                </div>
                <button id="confirm_btn" onclick="sendNewColor()">OK</button>
            </section>
            <span>
                <img class="input_icon" id="brightnessIcon">
                <input id="brightnessinput" type="range" value="122" min="0" max="255"
                    oninput="adaptBrightnessIndicator(this.value)" onchange="sendBrightness(this.value)">
                <p id="birghtness_value">50%</p>
            </span>
        </div>
        <div class="container">
            <section id="animation_section">
                <h3>Animations</h3>
                <hr>
                <ul id="animation_list">
                </ul>
            </section>
            <span>
                <img class="input_icon" id="animationspeedIcon">
                <input id="anim_speedinput" type="range" min="0" max="10"
                    oninput="adaptAnimationSpeedIndicator(this.value)" onchange="sendAnimationSpeed(this.value)">
                <p id="anim_speed_value">5</p>
            </span>
        </div>
    </div>
    <div id="navigationbar"><div id="topDivider"></div><p id="lightPanelBtn" onclick="movePanel(0)">Light</p><div id="middleDivider"></div><p id="animationsPanelBtn" onclick="movePanel(1)">Animations</p></div>

    <script>
        let animations = ["Solid", "Sparkle", "Fairytale", "Glow", "Fade"];
        let oldSelectedAnim = undefined;
        let canvas = getEl("colorwheel");
        let mainPanel = getEl("main_panel", true);
        let colorSelection = getEl("color_selection_panel");
        let background = getEl("bg", true);
        let lightPanelButton = getEl("lightPanelBtn"); 
        lightPanelButton.classList.add("selectedPanel");
        let animationsPanelButton = getEl("animationsPanelBtn"); 

        function getEl(element, isClass = false) {
            if (isClass) return document.getElementsByClassName(element)[0];
            else return document.getElementById(element);
        }

        (function () {
            fetch('http://192.168.178.52/getAnimation')
                .then(response => response.text())
                .then(data => console.log(data));
            let list = getEl("animation_list", false);
            for (let i = 0; i < animations.length; i++) {
                let newListElement = document.createElement("li");
                newListElement.innerHTML = animations[i];
                newListElement.addEventListener("click", function (ev) { changeAnimationSelection(this) });
                if (animations[i] == "Solid") {
                    newListElement.classList.add("selected_anim");
                    oldSelectedAnim = newListElement;
                }
                list.appendChild(newListElement);
                if (i < animations.length - 1) {
                    let newElementbreak = document.createElement("hr");
                    newElementbreak.classList.add("item-break");
                    list.appendChild(newElementbreak);
                }
            }
            getEl("brightnessIcon").src = 'data:image/png;base64,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';
            getEl("animationspeedIcon").src = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAHoAAAA8CAYAAACpWK6VAAAABHNCSVQICAgIfAhkiAAAAS9JREFUeJzt3DFOAzEQheHf24XrUG9Ly4mouBBp01LnOrg0hdMgESTkMZ6Q/zvByE9ejbRPBkmSlFEBaK09Ai/AE3BYOtHtqcAJeC2lnFcPc025hPyOAY+qwJ417I1+kw153IF+limV1toHBh2lllIeVg/xnW31APobG32RUIy0Z+kyFif3MnYZbAeO9GH1O5V+dmlDliRJkiRJkiRJknIpqwf4ie3UIV/aqWmDthARphciVk9xTWvtDXhePcc/ccwctO3UONUW6J3IHHTaRuUNOmX+dLuMxajAnvZG204dZjtVkiRJkiRJkiRJSU35H217c8iUt0XDg7YwECb0OasZxQPfFo0R+rbojBttezNO2NuiaatEijUjaNubccLO0mUsr9zLmO3NYbY3JUm6I58jr2HWmAygAgAAAABJRU5ErkJggg==';

        })();

        function movePanel(position){
            if(position == 0){
                lightPanelButton.classList.add("selectedPanel");
                animationsPanelButton.classList.remove("selectedPanel");
                mainPanel.classList.remove("main_panel_animations");
            } else {
                lightPanelButton.classList.remove("selectedPanel");
                animationsPanelButton.classList.add("selectedPanel");
                mainPanel.classList.add("main_panel_animations");
            }
        }

        function changeColorInput_BGColor(ele){
            ele.style.background = ele.value;
        }

        function changeAnimationSelection(element) {
            oldSelectedAnim.classList.remove("selected_anim");
            element.classList.add("selected_anim")
            oldSelectedAnim = element;
            sendAnimation(element);
        }

        function adaptBrightnessIndicator(value) {
            document.getElementById("birghtness_value").innerText = ((value / 255) * 100).toFixed(0) + "%";
        }

        function adaptAnimationSpeedIndicator(value) {
            document.getElementById("anim_speed_value").innerText = value;
        }

        function setColor(color, value) {
            if (color == "prim") {
                document.body.style.setProperty('--prim_color', value);
            } else {
                document.body.style.setProperty('--sec_color', value);
            }
        }
    </script>
    <script>
        //arduino communication and helpers
        let choosenColor = "";

        const hex2rgb = (hex) => {
            const r = parseInt(hex.slice(1, 3), 16)
            const g = parseInt(hex.slice(3, 5), 16)
            const b = parseInt(hex.slice(5, 7), 16)
            return [r, g, b]
        }

        function sendBrightness(value) {
            fetch('http://192.168.178.52/brightness?value=' + value)
                .then(response => response.text())
                .then(data => console.log(data));
        }

        function sendNewColor() {
            let newColor = getEl("prim_c").value
            if (newColor == choosenColor) return;
            choosenColor = newColor;
            let primcolor = hex2rgb(newColor);
            fetch('http://192.168.178.52/changeColor?color1=' + primcolor[0] + '&color2=' + primcolor[1] + '&color3=' + primcolor[2])
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error(error));
        }

        function sendAnimation(ele){
            fetch('http://192.168.178.52/animationType?value=' + ele.innerText)
                .then(response => response.text())
                .then(data => console.log(data));
        }

        function sendAnimationSpeed(value) {
            fetch('http://192.168.178.52/animationSpeed?value=' + value)
                .then(response => response.text())
                .then(data => console.log(data));
        }
    </script>
</body>

</html>
)=====";