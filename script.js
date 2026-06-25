// ===== SCREEN NAVIGATION =====
function showAnimation(name) {
    document.querySelectorAll('.screen').forEach(s => s.classList.remove('active'));
    document.getElementById(name + '-screen').classList.add('active');
    
    // Start the correct animation
    if (name === 'ball') startBall();
    if (name === 'car') startCar();
    if (name === 'triangle') startTriangle();
    if (name === 'cube') startCube();
}

function backToMenu() {
    document.querySelectorAll('.screen').forEach(s => s.classList.remove('active'));
    document.getElementById('menu-screen').classList.add('active');
    
    // Stop all animations to save CPU
    cancelAnimationFrame(ballFrame);
    cancelAnimationFrame(carFrame);
    cancelAnimationFrame(triangleFrame);
    cancelAnimationFrame(cubeFrame);
}

// ===== ANIMATION 1: BOUNCING BALL =====
// Converted from: bouncing_ball.cpp
let ballFrame;

function startBall() {
    const canvas = document.getElementById('ball-canvas');
    const ctx = canvas.getContext('2d');
    
    // Resize canvas to fill screen
    canvas.width = canvas.parentElement.clientWidth;
    canvas.height = canvas.parentElement.clientHeight - 60; // minus nav bar
    
    // === SAME VARIABLES FROM C++ ===
    let ballX = 250;
    let ballY = 250;
    let speedX = 3.0;
    let speedY = 2.5;
    let radius = 20;
    
    // === SAME DRAWCIRCLE FUNCTION ===
    function drawCircle(x, y, r) {
        ctx.beginPath();
        for (let i = 0; i < 360; i++) {
            let angle = i * Math.PI / 180;
            ctx.lineTo(x + Math.cos(angle) * r, y + Math.sin(angle) * r);
        }
        ctx.closePath();
        ctx.fill();
    }
    
    // === SAME DISPLAY FUNCTION ===
    function display() {
        // glClear(GL_COLOR_BUFFER_BIT) → clear canvas black
        ctx.fillStyle = 'black';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        // glColor3f(1.0, 0.0, 0.0) → red color
        ctx.fillStyle = 'red';
        drawCircle(ballX, ballY, radius);
    }
    
    // === SAME UPDATE FUNCTION ===
    function update() {
        ballX += speedX;
        ballY += speedY;
        
        // Bounce off walls
        if (ballX + radius > canvas.width || ballX - radius < 0) {
            speedX = -speedX;
        }
        if (ballY + radius > canvas.height || ballY - radius < 0) {
            speedY = -speedY;
        }
        
        display();
        ballFrame = requestAnimationFrame(update); // replaces glutTimerFunc
    }
    
    update(); // start animation
}

// ===== ANIMATION 2: MOVING CAR =====
// Converted from: moving_car.cpp
let carFrame;

function startCar() {
    const canvas = document.getElementById('car-canvas');
    const ctx = canvas.getContext('2d');
    
    canvas.width = canvas.parentElement.clientWidth;
    canvas.height = canvas.parentElement.clientHeight - 60;
    
    // === SAME VARIABLES FROM C++ ===
    let carX = 0.0;
    let speed = 2.0;
    
    // === SAME DRAWCAR FUNCTION ===
    function drawCar(x, y) {
        // Car body (blue) - GL_QUADS
        ctx.fillStyle = 'blue';
        ctx.fillRect(x, y, 100, 40);
        
        // Car roof (gray)
        ctx.fillStyle = 'gray';
        ctx.beginPath();
        ctx.moveTo(x + 20, y + 40);
        ctx.lineTo(x + 80, y + 40);
        ctx.lineTo(x + 70, y + 70);
        ctx.lineTo(x + 30, y + 70);
        ctx.closePath();
        ctx.fill();
        
        // Wheel 1 (black)
        ctx.fillStyle = 'black';
        ctx.fillRect(x + 15, y - 10, 20, 10);
        
        // Wheel 2 (black)
        ctx.fillRect(x + 65, y - 10, 20, 10);
    }
    
    function display() {
        // glClearColor(0.7, 0.7, 0.7) → light gray background
        ctx.fillStyle = '#b0b0b0';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        // Road (gray)
        ctx.fillStyle = '#808080';
        ctx.fillRect(0, 80, canvas.width, 20);
        
        // Draw car
        drawCar(carX, 80);
    }
    
    function update() {
        carX += speed;
        
        // Reset when off screen
        if (carX > canvas.width) {
            carX = -100;
        }
        
        display();
        carFrame = requestAnimationFrame(update);
    }
    
    update();
}

// ===== ANIMATION 3: ROTATING TRIANGLE =====
// Converted from: rotate_triangle.cpp
let triangleFrame;

function startTriangle() {
    const canvas = document.getElementById('triangle-canvas');
    const ctx = canvas.getContext('2d');
    
    canvas.width = canvas.parentElement.clientWidth;
    canvas.height = canvas.parentElement.clientHeight - 60;
    
    // === SAME VARIABLES ===
    let angle = 0.0;
    
    function display() {
        // glClearColor(0,0,0) → black background
        ctx.fillStyle = 'black';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        // glTranslatef(250, 250, 0) → move to center
        const cx = canvas.width / 2;
        const cy = canvas.height / 2;
        
        ctx.save();
        ctx.translate(cx, cy);
        
        // glRotatef(angle, 0, 0, 1) → rotate around Z
        ctx.rotate(angle * Math.PI / 180);
        
        // Draw triangle with RGB colors (GL_TRIANGLES)
        ctx.beginPath();
        
        // Vertex 1 (top) - Red
        ctx.fillStyle = 'red';
        ctx.moveTo(0, 120);
        
        // Vertex 2 (bottom left) - Green
        // For gradient effect, we use createLinearGradient
        const grad = ctx.createLinearGradient(0, -80, 0, 120);
        grad.addColorStop(0, 'red');
        grad.addColorStop(0.5, 'green');
        grad.addColorStop(1, 'blue');
        ctx.fillStyle = grad;
        
        ctx.lineTo(-100, -80);
        
        // Vertex 3 (bottom right) - Blue
        ctx.lineTo(100, -80);
        ctx.closePath();
        ctx.fill();
        
        // White outline (GL_LINE_LOOP)
        ctx.strokeStyle = 'white';
        ctx.lineWidth = 2;
        ctx.stroke();
        
        ctx.restore();
    }
    
    function update() {
        angle += 2.0;
        
        // Keep angle in range 0-360
        if (angle > 360) {
            angle -= 360;
        }
        
        display();
        triangleFrame = requestAnimationFrame(update);
    }
    
    update();
}

// ===== ANIMATION 4: ROTATING CUBE (3D) =====
// Converted from: rotating_cube.cpp
let cubeFrame;

function startCube() {
    const canvas = document.getElementById('cube-canvas');
    const ctx = canvas.getContext('2d');
    
    canvas.width = canvas.parentElement.clientWidth;
    canvas.height = canvas.parentElement.clientHeight - 60;
    
    // === SAME VARIABLES ===
    let angleX = 0.0;
    let angleY = 0.0;
    let angleZ = 0.0;
    
    // === SAME VERTICES ===
    const vertices = [
        [-1, -1, -1], [1, -1, -1], [1, 1, -1], [-1, 1, -1],  // back face
        [-1, -1, 1], [1, -1, 1], [1, 1, 1], [-1, 1, 1]       // front face
    ];
    
    // === SAME FACES WITH COLORS ===
    const faces = [
        { verts: [4, 5, 6, 7], color: '#ff0000' },  // front - red
        { verts: [0, 3, 2, 1], color: '#00ff00' },  // back - green
        { verts: [3, 7, 6, 2], color: '#0000ff' },  // top - blue
        { verts: [0, 1, 5, 4], color: '#ffff00' },  // bottom - yellow
        { verts: [1, 2, 6, 5], color: '#ff00ff' },  // right - magenta
        { verts: [0, 4, 7, 3], color: '#00ffff' }   // left - cyan
    ];
    
    function rotateX(v, angle) {
        const rad = angle * Math.PI / 180;
        return [v[0], v[1] * Math.cos(rad) - v[2] * Math.sin(rad), v[1] * Math.sin(rad) + v[2] * Math.cos(rad)];
    }
    
    function rotateY(v, angle) {
        const rad = angle * Math.PI / 180;
        return [v[0] * Math.cos(rad) + v[2] * Math.sin(rad), v[1], -v[0] * Math.sin(rad) + v[2] * Math.cos(rad)];
    }
    
    function rotateZ(v, angle) {
        const rad = angle * Math.PI / 180;
        return [v[0] * Math.cos(rad) - v[1] * Math.sin(rad), v[0] * Math.sin(rad) + v[1] * Math.cos(rad), v[2]];
    }
    
    function project(v) {
        // gluPerspective + glTranslatef(0, 0, -5)
        const scale = 100;
        const distance = 5;
        const z = v[2] + distance;
        return [
            canvas.width / 2 + (v[0] * scale) / z,
            canvas.height / 2 - (v[1] * scale) / z  // flip Y for canvas
        ];
    }
    
    function display() {
        // glClear → black
        ctx.fillStyle = 'black';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        // Apply rotations (same as glRotatef)
        let rotated = vertices.map(v => {
            v = rotateX(v, angleX);
            v = rotateY(v, angleY);
            v = rotateZ(v, angleZ);
            return v;
        });
        
        // Project to 2D
        const projected = rotated.map(v => project(v));
        
        // Draw faces with depth sorting (simple painter's algorithm)
        faces.forEach(face => {
            const avgZ = face.verts.reduce((sum, i) => sum + rotated[i][2], 0) / 4;
            
            // Only draw if facing camera (simple backface culling)
            if (avgZ > 0) {
                ctx.fillStyle = face.color;
                ctx.globalAlpha = 0.7;
                ctx.beginPath();
                ctx.moveTo(projected[face.verts[0]][0], projected[face.verts[0]][1]);
                for (let i = 1; i < face.verts.length; i++) {
                    ctx.lineTo(projected[face.verts[i]][0], projected[face.verts[i]][1]);
                }
                ctx.closePath();
                ctx.fill();
                ctx.globalAlpha = 1;
                
                // White edges
                ctx.strokeStyle = 'white';
                ctx.lineWidth = 1;
                ctx.stroke();
            }
        });
    }
    
    function update() {
        angleX += 1.0;
        angleY += 1.2;
        angleZ += 0.8;
        
        if (angleX > 360) angleX -= 360;
        if (angleY > 360) angleY -= 360;
        if (angleZ > 360) angleZ -= 360;
        
        display();
        cubeFrame = requestAnimationFrame(update);
    }
    
    update();
}