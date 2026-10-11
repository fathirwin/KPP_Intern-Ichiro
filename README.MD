Penjelasan Class
1. point: Mengelola koordinat dua dimensi (x, y) objek di lapangan serta menyediakan operator perbandingan == antar-objek.
2. field: Mengatur rendering visual lapangan dan menampilkan posisi robot (R), bola (O), serta sensor menggunakan ANSI Escape Code.
3. ball: Mengatur pergerakan bola, menerima efek tendangan (kick), dan menyimulasikan gaya gesek rumput (deceleration) agar bola melambat lalu berhenti.
4. robot (Base Class): Kelas abstrak dasar yang mengatur pergerakan standar robot, validasi batas 5. lapangan, dan memproyeksikan sensor pandangan ke depan.
6. striker (Turunan robot): Implementasi kecerdasan buatan (AI) robot penyerang menggunakan State Machine untuk mendeteksi, mengejar, dan bersiap menendang bola.
7. simulator: Mesin utama (Game Loop Engine) yang mengontrol waktu pertandingan (tick), mengoordinasikan interaksi antar-objek, dan memeriksa kondisi gol.

Penggunaan AI
1. Untuk brainstorming codingan.
2. Penggunaan Point meruapakn usul AI agar kodenya lebh rapi.