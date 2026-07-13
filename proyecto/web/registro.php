<?php

class RegistroUso
{
    private $conexion;

    public function __construct($conexion)
    {
        $this->conexion = $conexion;
    }

    
    public function obtenerTodos()
    {
        $sql = "SELECT * FROM registro
                ORDER BY fecha_hora DESC";

        return $this->conexion->query($sql);
    }

    public function obtenerTotal()
    {
        $sql = "SELECT COUNT(*) AS total
                FROM registro";

        $resultado = $this->conexion->query($sql);

        return $resultado->fetch_assoc();
    }


    public function obtenerPromedio()
    {
        $sql = "SELECT AVG(distancia) AS promedio
                FROM registro";

        $resultado = $this->conexion->query($sql);

        return $resultado->fetch_assoc();
    }

    public function obtenerUltimo()
    {
        $sql = "SELECT *
                FROM registro
                ORDER BY fecha_hora DESC
                LIMIT 1";

        $resultado = $this->conexion->query($sql);

        return $resultado->fetch_assoc();
    }

}