<?php
require_once "config/conexion.php";

echo "<h2>Conexión exitosa con TachInt.</h2>";
?>

<?php
require_once "config/conexion.php";
require_once "models/registro.php";

$registro = new Registro($conn);

$total = $registro->obtenerTotal();
$promedio = $registro->obtenerPromedio();
$ultimo = $registro->obtenerUltimo();
$registros = $registro->obtenerTodos();
?>

<!DOCTYPE html>
<html lang="es">

<head>

    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>TachInt</title>

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">

</head>

<body class="bg-light">

<div class="container mt-5">

    <h1 class="text-center mb-5">TachInt - Sistema de Monitoreo de Distancia</h1>

    <div class="row">

        <div class="col-md-4">

            <div class="card text-center shadow">

                <div class="card-body">

                    <h5>Total de usos</h5>

                    <h2><?= $total["total"] ?></h2>

                </div>

            </div>

        </div>

        <div class="col-md-4">

            <div class="card text-center shadow">

                <div class="card-body">

                    <h5>Distancia promedio</h5>

                    <h2><?= number_format($promedio["promedio"] ?? 0,2) ?> cm</h2>

                </div>

            </div>

        </div>

        <div class="col-md-4">

            <div class="card text-center shadow">

                <div class="card-body">

                    <h5>Último uso</h5>

                    <h2><?= $ultimo["fecha_hora"] ?? "no disponible" ?></h2>

                </div>

            </div>

        </div>

    </div>

    <div class="card shadow mt-5">

        <div class="card-header">Historial de usos</div>

        <div class="card-body">

            <table class="table table-hover">

                <thead>

                    <tr>

                        <th>ID</th>
                        <th>Fecha y Hora</th>
                        <th>Distancia</th>

                    </tr>

                </thead>

                <tbody>

                <?php while($fila = $registros->fetch_assoc()) { ?>

                    <tr>

                        <td><?= $fila["id"] ?></td>

                        <td><?= $fila["fecha_hora"] ?></td>

                        <td><?= $fila["distancia"] ?> cm</td>

                    </tr>

                <?php } ?>

                </tbody>

            </table>

        </div>

    </div>

</div>

</body>

</html>