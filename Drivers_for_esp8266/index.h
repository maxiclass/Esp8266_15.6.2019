const char MAIN_page[]  =
R"(













<html lang='en'>
<head>
    <title>Dim an RGB LED</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css' />
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css' />
    <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
</head>
<body>
    <div class='container-fluid text-center'>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Drone project setup -> AXE 1114C.</p>
            </div>
        </div>
        <br />
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:3vh'>
                Red:
                <b id='status1'></b>
            </div>
        </div>
        <div class='col-sm-12'>
            <input type='range' min='0' max='100' class='form-control-range' id='slider_red' />
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:green;font-size:3vh'>
                Green:
                <b id='status2'></b>
            </div>
        </div>
        <div class='col-sm-12'>
            <input type='range' min='0' max='100' class='form-control-range' id='slider_green' />
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:blue;font-size:3vh'>
                Blue:
                <b id='status3'></b>
            </div>
        </div>
        <div class='col-sm-12'>
            <input type='range' min='0' max='100' class='form-control-range' id='slider_blue' />
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:blue;font-size:3vh'>
                Motor4:
                <b id='statusMotor4'></b>
            </div>
        </div>
        <div class='col-sm-12'>
            <input type='range' min='0' max='100' class='form-control-range' id='slider_Motor4' />
        </div>



        <!-- Insert New HTML elements for servo motor. -->
        <div class='row'>
            <div class='col-sm-12' style='color:blue;font-size:3vh'>
                Servo motor:
                <b id='statusServo'></b>
            </div>
        </div>
        <div class='col-sm-12'>
            <input type='range' min='0' max='180' class='form-control-range' id='slider_Servo' />
        </div>
        <!-- Insert New HTML elements for servo motor. -->
        <div class="btn-group btn-group-lg">
            <button type="button" class="btn btn-primary">Analog</button>
            <button type="button" class="btn btn-primary">Analog</button>
            <button type="button" class="btn btn-primary">Web</button>
        </div>
    </div>
    </div>
</body>

<!-- new elements for printing ACC and GYR (posible MAG) measurements -->


<style>
    .sensor_representation_A {
        position: absolute;
        max-width: 150px;
        min-height: 100px;
        background: #02b875;
        padding: 20px;
        box-sizing: border-box;
        color: #FFF;
        margin: 20px;
        box-shadow: 0px 2px 15px -4px rgba(0,0,0,0.75);
    }

    .sensor_representation_B {
        position: absolute;
        left: +200px;
        max-width: 150px;
        min-height: 100px;
        background: #02b875;
        padding: 20px;
        box-sizing: border-box;
        color: #FFF;
        margin: 20px;
        box-shadow: 0px 2px 15px -4px rgba(0,0,0,0.75);
    }

    .sensor_representation_C {
        position: absolute;
        left: +400px;
        max-width: 150px;
        min-height: 100px;
        background: #02b875;
        padding: 20px;
        box-sizing: border-box;
        color: #FFF;
        margin: 20px;
        box-shadow: 0px 2px 15px -4px rgba(0,0,0,0.75);
    }
</style>



<body>

    <div class="sensor_representation_A">

        <h6>Accelermeter</h6><br>
        <h6>AX:<span id="AccelermeterValueX">0</span></h6><br>
        <h6>AY:<span id="AccelermeterValueY">0</span></h6><br>
        <h6>AZ:<span id="AccelermeterValueZ">0</span></h6><br>
    </div>

    <div class="sensor_representation_B">
        <h6>Gyroscope</h6><br>
        <h6>GX:<span id="GyroscopeValueX">0</span></h6><br>
        <h6>GY:<span id="GyroscopeValueY">0</span></h6><br>
        <h6>GZ:<span id="GyroscopeValueZ">0</span></h6><br>
    </div>

    <div class="sensor_representation_C">
        <h6>Magnetormeter</h6><br>
        <h6>MX:<span id="MagnetormeterValueX">0</span></h6><br>
        <h6>MY:<span id="MagnetormeterValueY">0</span></h6><br>
        <h6>MZ:<span id="MagnetormeterValueZ">0</span></h6><br>
    </div>

</body>














<script>

    setInterval(function () {
        // Call a function repetatively with 2 Second interval
        getData();
    }, 10); //10mSeconds update rate

    function getData() {
        vSend_Mpu_Ax_to_web();
        vSend_Mpu_Ay_to_web();
        vSend_Mpu_Az_to_web();

        vSend_Mpu_Gx_to_web();
        vSend_Mpu_Gy_to_web();
        vSend_Mpu_Gz_to_web();

        vSend_Mpu_Mx_to_web();
        vSend_Mpu_My_to_web();
        vSend_Mpu_Mz_to_web();
    }

//functions for sending web data from MPU -> ACC
    function vSend_Mpu_Ax_to_web()
    {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("AccelermeterValueX").innerHTML =
                    this.responseText;
            }
        };
        xhttp.open("GET", "vSend_Mpu_Ax_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_Ay_to_web()
    {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("AccelermeterValueY").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Ay_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_Az_to_web()
    {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("AccelermeterValueZ").innerHTML =
                    this.responseText;
            }
        };
        xhttp.open("GET", "vSend_Mpu_Az_to_web", true);
        xhttp.send();
    }

//functions for sending web data from MPU -> GYR
    function vSend_Mpu_Gx_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("GyroscopeValueX").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Gx_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_Gy_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("GyroscopeValueY").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Gy_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_Gz_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("GyroscopeValueZ").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Gz_to_web", true);
        xhttp.send();
    }
//functions for sending web data from MPU -> MAG

    function vSend_Mpu_Mx_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("MagnetormeterValueX").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Mx_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_My_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("MagnetormeterValueY").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_My_to_web", true);
        xhttp.send();
    }
    function vSend_Mpu_Mz_to_web()
        {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("MagnetormeterValueZ").innerHTML = this.responseText;}
        };
        xhttp.open("GET", "vSend_Mpu_Mz_to_web", true);
        xhttp.send();
    }








    $('#slider_red').on('change', function () {
        var state_slider_red = $('#slider_redslider_red').val();

        $('#status1').html(state_slider_red + ' %');

        $.ajax({
            url: '/redFunction',
            type: 'POST',
            data: { state1: state_slider_red }
        });
    });

    $('#slider_green').on('change', function () {
        var state_slider_green = $('#slider_green').val();

        $('#status2').html(state_slider_green + ' %');

        $.ajax({
            url: '/greenFunction',
            type: 'POST',
            data: { state2: state_slider_green }
        });
    });

    $('#slider_blue').on('change', function () {
        var state_slider_blue = $('#slider_blue').val();

        $('#status3').html(state_slider_blue + ' %');

        $.ajax({
            url: '/blueFunction',
            type: 'POST',
            data: { state3: state_slider_blue }
        });
    });

    $('#slider_Motor4').on('change', function () {
        var state_slider_Motor4 = $('#slider_Motor4').val();

        $('#statusMotor4').html(state_slider_Motor4 + ' %');

        $.ajax({
            url: '/Motor4Function',
            type: 'POST',
            data: { statusMotor4: state_slider_Motor4 }
        });
    });

    //Insert script for servomotor control
    $('#slider_Servo').on('change', function () {
        var slider_Servo = $('#slider_Servo').val();

        $('#statusServo').html(slider_Servo + ' º');

        $.ajax({
            url: '/MoveServoFunction',
            type: 'POST',
            data: { statusServo: slider_Servo }
        });
    });
</script>
</html>






)";
