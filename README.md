# Telematica‑Vautonomo‑P1

Servidor de telemetría y control para un vehículo simulado (**C + Sockets TCP**), con clientes de referencia en **Python** y **Java**. Incluye un **protocolo RFC‑lite VEHI/1.0** y guías de build/ejecución en Windows (MSYS2 MinGW‑w64).

> **Estado del repo:** académico • multi‑cliente • listo para demo en LAN

---

## Estructura

```
server-c/           # Código fuente del servidor en C
client-python/      # Cliente de referencia (Python, CLI/GUI mínima)
client-java/        # Cliente de referencia (Java, consola)
.vscode/            # Tasks para lanzar clientes (opcional)
docs/               # Documentación (RFC‑lite, diagramas)
```

## Prerrequisitos

* **Windows 10/11**
* **MSYS2** con toolchain **mingw32**: `mingw-w64-i686-toolchain`
* **Python 3.10+** (en PATH)
* **Java 11+ JDK** (en PATH)
* (Opcional) **VS Code**

> Si vas a ejecutar `server.exe` fuera de MSYS2, añade `C:\msys64\mingw32\bin` al **PATH** o copia las DLLs requeridas (p. ej., `libwinpthread-1.dll`) junto al binario.

---

## Compilar el servidor (MSYS2 MinGW 32‑bit)

```bash
# Abrir "MSYS2 MinGW 32-bit"
cd /c/ruta/al/repo/serve-c
mingw32-make clean
mingw32-make
```

El binario queda en:

```
build/server.exe
```

## Ejecutar el servidor

```bash
cd /c/ruta/al/repo/server-c/build
./server.exe 5000 server.log
```

* Permite el **Firewall** la primera vez.
* Cambia el puerto si está en uso (p. ej., 5050).

### Ver el log desde PowerShell

```powershell
Get-Content C:\ruta\al\repo\server-c\build\server.log -Tail 50 -Wait
```

---

## Probar desde consola tipo "telnet"

### Con Telnet (Windows)

```powershell
telnet 127.0.0.1 5000
```

Comandos útiles:

```
SUBSCRIBE TELEMETRY
PING
AUTH username=admin password=changeme
COMMAND SPEED UP token=TU_TOKEN
```

### Alternativa PowerShell (sin Telnet)

```powershell
$client = New-Object System.Net.Sockets.TcpClient("127.0.0.1",5000)
$stream = $client.GetStream()
$w = New-Object IO.StreamWriter($stream); $w.NewLine="`r`n"; $w.AutoFlush=$true
$w.WriteLine("SUBSCRIBE TELEMETRY")
```

---

## 🐍 Cliente Python (observer/admin)

### Ejecutar (observer)

```bash
python client-python/main.py --host 127.0.0.1 --port 5000 --subscribe
```

### Ejecutar (admin)

```bash
python client-python/main.py --host 127.0.0.1 --port 5000 --mode admin --user admin --pass changeme --subscribe
```

En el REPL puedes enviar:

```
PING
SUBSCRIBE TELEMETRY
AUTH username=admin password=changeme
COMMAND TURNL
```

---

## Cliente Java (observer/admin)

### Compilar

```bash
javac client-java/Client.java
```

### Ejecutar (observer)

```bash
java -cp client-java Client --host 127.0.0.1 --port 5000 --mode observer --subscribe true
```

### Ejecutar (admin)

```bash
java -cp client-java Client --host 127.0.0.1 --port 5000 --mode admin --user admin --pass changeme --subscribe true
```

---

## Protocolo (RFC‑lite VEHI/1.0)

* Mensajería **texto+CRLF**.
* Roles: **Admin** (requiere `AUTH`) y **Observer** (`SUBSCRIBE TELEMETRY`).
* Comandos: `AUTH`, `SUBSCRIBE/UNSUBSCRIBE`, `COMMAND <SPEED UP|SLOW DOWN|TURN LEFT|TURN RIGHT> token=...`, `PING`, `LIST USERS` (admin).
* Eventos: `TELEMETRY speed=<f> battery=<int> heading=<N|E|S|W> ts=<ms> [x=<f> y=<f>]`.
* Códigos: `200 OK`, `400 BAD REQUEST`, `401 UNAUTHORIZED`, `403 FORBIDDEN`, `409 CANNOT EXECUTE reason=...`.

El documento completo está [Aquí](./docs/RFC)

---

## VS Code (opcional)

Tareas para lanzar clientes sin compilar server:

* **Client Python - Observer**
* **Client Python - Admin**
* **Client Java - Build**
* **Client Java - Observer**
* **Client Java - Admin**

> Asegúrate de colocar `.vscode/tasks.json` en la raíz del repo.

---

## Troubleshooting

* `address in use`: cambia puerto o libera el PID (`netstat -ano | findstr 5000` → `taskkill /PID <PID> /F`).
* No llegan datos: envía `SUBSCRIBE TELEMETRY` tras conectar.
* Ejecutando desde PowerShell pide DLL: agrega `C:\msys64\mingw32\bin` al **PATH** o copia la DLL junto al `.exe`.
* "undefined reference to WSA.../pthread..." al compilar: enlaza `-lws2_32 -lpthread` (Makefile ya lo incluye).

---
