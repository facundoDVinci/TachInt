import serial # Comunicación por puerto serie
import mysql.connector # Conexión con MySQL

# Se establece la conexión con el Arduino.
# COM3 corresponde al puerto donde Windows detecta el dispositivo.
arduino = serial.Serial("COM3", 9600, timeout=1) 

# Conexión con la base de datos
conexion = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="tachint"
)

cursor = conexion.cursor() 

print("Esperando datos...")

# El programa permanece ejecutándose constantemente esperando mensajes provenientes del Arduino.
while True:
    # Verifica si existe información disponible
    if arduino.in_waiting > 0:

        mensaje = arduino.readline().decode("utf-8").strip() # Lee una línea enviada por el Arduino

        print(mensaje)
        # Solo se procesan mensajes que comiencen con "USO,"
        if mensaje.startswith("USO,"):

            try:
                distancia = float(mensaje.split(",")[1])  # Obtiene únicamente el valor numérico

                sql = "INSERT INTO registro (distancia) VALUES (%s)"  # Consulta SQL para guardar el registro
                cursor.execute(sql, (distancia,))
                conexion.commit()  # Guarda definitivamente el registro

                print("Uso registrado correctamente.") 

            except Exception as e:
                print("Error:", e) # Muestra cualquier error ocurrido