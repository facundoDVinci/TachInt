import serial
import mysql.connector

arduino = serial.Serial("COM3", 9600, timeout=1)

conexion = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="tachint"
)

cursor = conexion.cursor()

print("Esperando datos...")

while True:

    if arduino.in_waiting > 0:

        mensaje = arduino.readline().decode("utf-8").strip()

        print(mensaje)

        if mensaje.startswith("USO,"):

            try:
                distancia = float(mensaje.split(",")[1])

                sql = "INSERT INTO registro (distancia) VALUES (%s)"
                cursor.execute(sql, (distancia,))
                conexion.commit()

                print("Uso registrado correctamente.")

            except Exception as e:
                print("Error:", e)