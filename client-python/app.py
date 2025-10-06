import socket, threading, tkinter as tk
from tkinter import font

HOST='127.0.0.1'; PORT=5000

class App:
    def __init__(self, root):
        self.root = root
        root.title("Telemetría - Python")
        self.speed=tk.StringVar(value="0.00"); self.bat=tk.StringVar(value="0")
        root.geometry("400x300")
        self.label_font = font.Font(family="Arial", size=14)
        self.value_font = font.Font(family="Arial", size=18, weight="bold")
        self.temp=tk.StringVar(value="0.0");  self.head=tk.StringVar(value="-")

        for i,(k,v) in enumerate([("Velocidad",self.speed),("Batería",self.bat),
                                  ("Temp",self.temp),("Dirección",self.head)]):
            tk.Label(root,text=k+":", font=self.label_font).grid(row=i,column=0,sticky="e", padx=5, pady=5)
            tk.Label(root,textvariable=v, font=self.value_font).grid(row=i,column=1,sticky="w",padx=5,pady=5)

        self.sock = socket.create_connection((HOST,PORT))
        self.sock.sendall(b"SUBSCRIBE TELEMETRY\r\n")
        threading.Thread(target=self.reader, daemon=True).start()

    def reader(self):
        buf=b""
        while True:
            chunk = self.sock.recv(1024)
            if not chunk: break
            buf += chunk
            while b"\r\n" in buf:
                line, buf = buf.split(b"\r\n",1)
                self.process(line.decode(errors='ignore'))

    def process(self, line):
        if line.startswith("TELEMETRY"):
            parts = dict(kv.split("=",1) for kv in line.split()[1:])
            self.root.after(0, lambda: self.update_ui(parts))

    def update_ui(self, p):
        self.speed.set(p.get("speed","0.00"))
        self.bat.set(p.get("battery","0"))
        self.temp.set(p.get("temp","0.0"))
        self.head.set(p.get("heading","-"))

if __name__=="__main__":
    root=tk.Tk(); App(root); root.mainloop()
