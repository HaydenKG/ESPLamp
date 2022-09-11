const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>HLED control</title>
    <link rel="icon"  type="image/png" sizes="16x16" href="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABHNCSVQICAgIfAhkiAAAAglJREFUOI2lk71rU1EYh59zk8bbJNVbDcZo0dI6qEtiHAQnMSAUBy+CSxYv/gOmk+Li0smlcVQQHKQZvZtQqGgXEWw0DuIH7Y2StrQUkt6oyc3HPQ75sPnApe90eM/v97wfnAP7DDGQKX7QyAfv8DOke1a1mJaFQ1k+ap8xT8IjE1HaK1d6zPKpweiuRaAaxl+ba44w5XWY8vxm7hSNaxq1zYfYxvBe5A0DeddCLughef54//U93/qD+yPbmQWK1jLbXYgCMCljmp+1efg0i0iayPp6P2Bc3WBs1Po6TXN2ksZ8EUvrAk6zkzqLnUG8NAEmnPpAg5paQFMLXCRkHmEto5JNdQFnKOtRSksd8YnqEIC/gOYvAODl9ZKHt9dbZ+Acu9EmZDviWLnCzKvpx8H8GMEfBwnkA6jf3l/w/vKVAXwsZl1qsS7gWAO8jX/V/E0XYMVF4goXkBygFvF6mpsAqMsoEnDagHCTnE8hDlgAEafO7SurT/aO8P3S5Yjrb7+bEHHq5Nhq7+BoHTNcJdER/2+JABwmwThmd4RQg3QA8nKLRRHGnBi2xJZZyqvoVEhSZrJHIAsY7hcs+Q7dfqPIAQIgDXR5E0vOoHdyPX9BrmBImzQ2XrHDLTbI4gB/iLsVEqJGUjgY4nmr/QEAgHyB5lZJUUKXRaKiAjjkqGIqNmnxjFK/Z1/xF8lNxL1iFSVSAAAAAElFTkSuQmCC"/>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@300&display=swap');

        :root {
            --prim_color: rgb(205, 20, 0);
            --sec_color: rgb(0, 0, 0);
        }

        body {
            background: linear-gradient(135deg, var(--prim_color), var(--sec_color));
            width: 100%;
            max-width: 800px;
            height: 100vh;
            margin: 0;
            font-family: 'Open Sans', sans-serif;
            color: #fefefe;
            font-size: 1.5rem;
        }

        input[type="range"] {
            -webkit-appearance: none;
            width: 70%;
            border-radius: 5px;
            background-color: rgb(139, 139, 139);
            accent-color: #fff;
            background-image: linear-gradient(to right, #ffffff, #ffffff);
            background-size: 55% 100%;
            background-repeat: no-repeat;
        }

        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            height: 30px;
            width: 30px;
            border-radius: 5px;
            background: #ffffff;
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
            overflow-y: auto;
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

        h3, h4 {
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
            height: 90%;
            padding: 5% 0;
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
        }

        .container {
            display: grid;
            grid-template-rows: auto;
            justify-content: space-evenly;
            align-content: space-evenly;
            align-items: start;
            width: 50%;
            height: 100%;
        }

        .input_icon {
            width: 60px;
            margin: 15px 0;
        }

        .iconWrapper {
            flex-direction: row;
            justify-content: space-between;
            width: 80%;
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
            left: 5vw;
            width: 90vw;
            height: 50px;
            padding: 10px 0;
            display: grid;
            grid-template-columns: 1fr .1fr 1fr;
            justify-items: center;
            align-items: center;
        }

        #navigationbar p {
            margin: 0;
        }

        .selectedPanel {
            font-weight: 800;
            transform: scale(1.05);
            transition: all .2s;
        }

        #topDivider{
            position: absolute;
            width: 90%;
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
    <h1 id="heading">HLED control</h1>
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
                <button id="confirm_btn" onclick="sendNewColor()">Send</button>
            </section>
            <span>
                <span class="iconWrapper">
                    <img class="input_icon" id="brightnessIconDim">
                    <p id="birghtness_value">50%</p>
                    <img class="input_icon" id="brightnessIconBright">
                </span>
                <input id="brightnessinput" type="range" value="127.5" min="0" max="255" step="5"
                    oninput="adjustinputRange(this, '')" onchange="sendBrightness(this.value)">
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
                <span class="iconWrapper">
                    <img class="input_icon" id="animSpeedIconSlow">
                    <p id="anim_speed_value">5</p>
                    <img class="input_icon" id="animSpeedIconFast">
                </span>
                <input id="anim_speedinput" type="range" min="0" max="10"
                    oninput="adjustinputRange(this, 'anim')" onchange="sendAnimationSpeed(this.value)">
            </span>
        </div>
    </div>
    <div id="navigationbar">
        <div id="topDivider"></div>
        <p id="lightPanelBtn" onclick="movePanel(0)">Light</p>
        <div id="middleDivider"></div>
        <p id="animationsPanelBtn" onclick="movePanel(1)">Animations</p>
    </div>

    <script>
        let animations = ["Solid", "Confetti", "Rainbow"];
        let oldSelectedAnim = undefined;
        let canvas = getEl("colorwheel");
        let mainPanel = getEl("main_panel", true);
        let colorSelection = getEl("color_selection_panel");
        let background = getEl("bg", true);
        let lightPanelButton = getEl("lightPanelBtn"); 
        lightPanelButton.classList.add("selectedPanel");
        let animationsPanelButton = getEl("animationsPanelBtn"); 
        getEl("confirm_btn", false).style.visibility = "hidden";
        adjustinputRange(getEl("brightnessinput"), "", true);
        adjustinputRange(getEl("anim_speedinput"), "anim", true);

        function getEl(element, isClass = false) {
            if (isClass) return document.getElementsByClassName(element)[0];
            else return document.getElementById(element);
        }

        function initAnimationList(animation_list){
            animation_list = animation_list.filter(n => n);
            console.log(animation_list);
            let list = getEl("animation_list", false);
            if(list.childElementCount > 0)
                list.replaceChildren()

            for (let i = 0; i < animation_list.length; i++) {
                let newListElement = document.createElement("li");
                newListElement.innerHTML = animation_list[i];
                newListElement.addEventListener("click", function (ev) { changeAnimationSelection(this) });
                if (animation_list[i] == "Solid") {
                    newListElement.classList.add("selected_anim");
                    oldSelectedAnim = newListElement;
                }
                list.appendChild(newListElement);
                if (i < animation_list.length - 1) {
                    let newElementbreak = document.createElement("hr");
                    newElementbreak.classList.add("item-break");
                    list.appendChild(newElementbreak);
                }
            }
        }

        (async function () {
            getEl("brightnessIconDim").src = 'data:image/png;base64,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';
            getEl("brightnessIconBright").src = 'data:image/png;base64,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';
            getEl("animSpeedIconSlow").src = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAABHNCSVQICAgIfAhkiAAABXJJREFUeJzt3c/LZmUdx/HPt1oYZrsoUSxb5GQuKnOW44+WM+CuUhfWIgKrRYuBFkIE7dwEE0QUFGFmbatlOdnOiWLIpinCMhwU2vUkuepq8dxBhBQ4576/zznX6/UXvLl4zmfO/WPOnQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAALBh1R1wEowxbkjysST3JbkjyU2tQSfDUZLfJ7mY5IdV9VpvDvsw/QCMMR5Pcj7J27tbTrC/JXmiqr7SHcKyph2AMcatSb6X5Ex3y4o8m+SRqnqpO4RlTDkAY4x3JPlZkru6W1bo+SQPVNVfu0O4fm/qDmjyzbj436i7cnx+bMB0AzDGeCTJg90dK/fg7hxZuekGIMlnuwM2wjluwFTvAYwx3pfjj7ZYxh1V9YfuCN642e4ATncHbIzzXLnZBuC27oCNcZ4rN9sAvKU7YGOc58rNNgA+u16W81y52QbgN90BG+M8V26qTwGSZIzxcpJ3dXdswCtVdXN3BNdntjuAJPlWd8BGOMcNmPEO4MYkV5Pc2t2yYi8lOVVVr3aHcH2muwPY/dE+1t2xco+5+LdhugFIkqr6UZJHuztW6tHd+bEBUw5AklTVd3P8LIDnultW4rkkZ3bnxkZM9x7A6xljPJzk4SQPJHlrc85J8o8cPzfhqap6qjuG5RmA/zLGeE88EzBJjqrqz90RAAAAAAAAAAAAAAAAAAAAAAAAABvmmYCTG2N8Msm5JPckuSXJm1uD9usoxz8K80ySp6vq18097QzApHYX/peT3Nac0unJJOer6pXukC4GYEJjjAtJPtfdcUJcS/JQVf2iO6SDAZiMi/91HSW5d8aXBAZgIrvb/m93d5xQl6rqdHfEoRmAiYwxXszcr/n/ny9U1Ve7Iw5p2t8GnM3uX38X///2me6AQzMA8zjXHbACp8YYH+qOOCQDMI97ugNW4sPdAYdkAOZxS3fAStzcHXBIBgAmZgDmca07YCVe7g44JAMwj0vdASvxq+6AQzIA8/hxd8AKXJ3t24AGYBJV9Z0kf+nuOOG+0R1waAZgLl/qDjjBLs32LcDEAExldxfwte6OE+goE34LMDEA06mqz8cI/KdrSc7O9tr/3wzAhHYj8Kl4T+DJJB+Z9VkAif8NOD2PBAMAAAAAAAAAAAAAAAAAAAAAAOjmkWAHMsa4IcnbujtOmL9X1WvdETMzAHs0xvhokoeS3J/kvc05J9ULOX5G3/er6qfdMbMxAHswxnh/kieSnO1uWZmfJDlfVb/rDpmFAVjYGONckqeT3NjdslKvJvlEVfktwwMwAAsaY5xJ8vPujo24t6qe7Y7YOgOwoDHGb5Pc2d2xEVeq6gPdEVvnl4EWMsb4Ylz8S7pzd6bskTuAhYwxXkhye3fHxvypqnx6skfuABYwxjgdF/8+3L47W/bEACzjg90BG+Zs98gALOOd3QEb5mz3yAAs45/dARvmbPfIACzjWnfAhjnbPTIAy/hld8CGOds9MgALqKrnk1zu7tigy7uzZU8MwHK+3h2wQc50z3wRaEFjjGeS3NfdsREXq+r+7oitcwewrE/Hm1ZLuJbjs2TPDMCCquqPOX4GwJXulhW7kuTs7izZMwOwsKq6nOTuJBe6W1boQpK7d2fIAXgPYI/GGO9O8vEcvy9wKslNrUEnz1GSq0kuJvlBVb3YmwMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFv0L10D6p+FzKokAAAAAElFTkSuQmCC';
            getEl("animSpeedIconFast").src = 'data:image/png;base64,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';

            initAnimationList(animations);

            await fetch('http://192.168.178.52/getAnimation')
                .then(response => response.text())
                .then(data => initAnimationList(data.split(",")))
                .catch((error) => {
                    console.warn(error);
                });
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

        function setColor(color, value) {
            if (color == "prim") {
                document.body.style.setProperty('--prim_color', value);
            } else {
                document.body.style.setProperty('--sec_color', value);
            }
            getEl("confirm_btn", false).style.visibility = "visible";
        }

        function adjustinputRange(ele, type, init = false){
            if(!init){
                if(type == "anim"){
                    getEl("anim_speed_value").innerText = ele.value;
                } else {
                    getEl("birghtness_value").innerText = ((ele.value / 255) * 100).toFixed(0) + '%';
                }
            }

            const minVal = ele.min;
            const maxVal = ele.max;
            const currentVal = ele.value;
  
            ele.style.backgroundSize = (currentVal - minVal) * 100 / (maxVal - minVal) + '% 100%'
        }
    </script>
    <script>
        //arduino communication and helpers

        function sendBrightness(value) {
            fetch('http://192.168.178.52/brightness?value=' + value)
                .then(response => response.text())
                .then(data => console.log(data));
        }

        function sendNewColor() {
            let priColor = getEl("prim_c").value;
            priColor = priColor.replace("#", "0x");
            let primaryColor = parseInt(priColor);

            let secColor = getEl("sec_c").value;
            secColor = secColor.replace("#", "0x");
            let secondaryColor = parseInt(secColor);

            getEl("confirm_btn", false).style.visibility = "hidden";
            fetch('http://192.168.178.52/changeColor?color1=' + primaryColor + '&color2=' + secondaryColor)
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