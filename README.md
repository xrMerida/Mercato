# Mercato

Mercato es un simulador de compra/venta de jugadores de fútbol. El jugador
administra uno de seis clubes disponibles, y sera capaz de controlar su
presupuesto en millones euros (€ M), negociar transferencias y avanza la
simulación durante una cantidad limitada de días.

# Manual de Usuario

## Inicializacion

Antes de iniciar la simulación, se le pide al usuario que seleccione los
siguientes datos:

1. Seleccionar uno de los clubes para administrar.
2. Días que durara la simualción (de 5 a 15).
3. Revisar las elecciones tomadas

## Menú principal

### Ver Club

Muestra la plantilla actual del club, el valor de cada jugador, el presupuesto
disponible y la cantidad de jugadores.

### Explorar Jugadores

Permite consultar jugadores de cualquier club mediante estas opciones:

- **Ver todos:** muestra todos los clubes y sus jugadores
- **Filtrar por posición:** filtra por portero, defensa, mediocampista o
  delantero.
- **Buscar por ID:** muestra la información de un jugador específico.

> Cada jugador tiene un ID, nombre, posición, club y valor de mercado.

### Realizar Oferta

El usuario puede realizar ofertas por jugadores de otros clubes, para ello
se le solicita:

1. El ID del jugador a realizar la oferta
2. Cuantos millones de euroes `€ M` ofertara por el jugador

> No puede ofertar por un jugador de su propio club

> No puede ofertar dos veces por el mismo jugador

Al avanzar el día, una oferta de compra se acepta si alcanza al menos el 110 %
del valor actual del jugador y el club del usuario tiene presupuesto
suficiente.

### Revisar Ofertas

Otros clubes ofertaran por jugadores del club del usuario. El usuario tiene la
opcion de:

1. Aceptar
2. Rechazar

Cada transacción realizada queda registrada y se mostrara en el resumen final

### Ver Historial

Muestra las transferencias realizadas, indicando:

- Día realizada
- Jugador transferido
- Club de origen
- Club de destino
- Monto de la operación.

### Avanzar de día

Al avanzar de días se procesan los siguientes aspectos:

- Ofertas que el usuario haya realizado anteriormente.
- Actualización del valor de los jugadores (± 5 %).
- El juego termina si se ha llegado al ultimo día.

## Reporte final

Al terminar la simulación se muestra:

- La plantilla inicial y la plantilla final.
- El presupuesto inicial y final.
- El total gastado en compras.
- El total recibido por ventas.
- La cantidad de ofertas aceptadas y rechazadas.
- El historial de transferencias.

## Controles de entrada

- Los menús aceptan números correspondientes a las opciones mostradas.
- Las preguntas de confirmación aceptan `S`/`s` para sí y `N`/`n` para no.
- Si se ingresa un valor invalido, se ignora.

# Contribuciones

## Analisis y Diseño (Fase 01)

| Seccion                | Desarollador       | Porcentaje |
| ---------------------- | ------------------ | ---------- |
| Entradas               | Sebastían Gonzáles | 05%        |
| Procesos               | Sebastían Gonzáles | 05%        |
| Salidas                | Xavier Mérida      | 05%        |
| Validaciones           | Xavier Mérida      | 05%        |
| Seleccion de jugadores | Xavier Mérida      | 02%        |
| Diagrama de clases     | Xavier Mérida      | 39%        |
| Diagrama de flujo      | Sebastían Gonzáles | 39%        |

## Desarollo del Programa (Fase 02)

| Parte                        | Desarollador       | Porcentaje |
| ---------------------------- | ------------------ | ---------- |
| Logica `Jugador` y derivadas | Xavier Mérida      | 2%         |
| Logica `Jugador` y derivadas | Sebastían Gonzáles | 3%         |
| Logica `Simulador`           | Xavier Mérida      | 35%        |
| Logica `Simulador`           | Sebastían Gonzáles | 45%        |
| Logica de `main`             | Xavier Mérida      | 5%         |
| Logica de `main`             | Sebastían Gonzáles | 2%         |
| Interfaz de usuario          | Xavier Mérida      | 8%         |

## Licencia

Este proyecto está bajo la licencia GPLv3. Ver el archivo [LICENSE](LICENSE) para más detalles.
