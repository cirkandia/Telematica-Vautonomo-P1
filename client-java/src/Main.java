import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.*;
import java.util.*;

public class Main {
  public static void main(String[] args) throws Exception {
    JFrame f = new JFrame("Telemetría - Java");
    JLabel lSpeed=new JLabel("0.00"), lBat=new JLabel("0"), lTemp=new JLabel("0.0"), lHead=new JLabel("-");
    f.setLayout(new GridLayout(4,2));
    f.add(new JLabel("Velocidad:")).setFont(new Font("Arial", Font.PLAIN,18)); f.add(lSpeed).setFont(new Font("Arial", Font.PLAIN,18));
    f.add(new JLabel("Batería:")).setFont(new Font("Arial", Font.PLAIN,18));   f.add(lBat).setFont(new Font("Arial", Font.PLAIN,18));
    f.add(new JLabel("Temp:")).setFont(new Font("Arial", Font.PLAIN,18));      f.add(lTemp).setFont(new Font("Arial", Font.PLAIN,18));
    f.add(new JLabel("Dirección:")).setFont(new Font("Arial", Font.PLAIN,18)); f.add(lHead).setFont(new Font("Arial", Font.PLAIN,18));
    f.pack(); f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); f.setVisible(true);
    f.setSize(400,400);

    Socket s = new Socket("127.0.0.1", 5000);
    OutputStream out = s.getOutputStream();
    out.write("SUBSCRIBE TELEMETRY\r\n".getBytes()); out.flush();

    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    String line;
    while ((line=br.readLine())!=null) {
      if (line.startsWith("TELEMETRY")) {
        Map<String,String> m = new HashMap<>();
        String[] toks = line.split(" ");
        for (int i=1;i<toks.length;i++) {
          String[] kv = toks[i].split("=",2);
          if (kv.length==2) m.put(kv[0], kv[1]);
        }
        SwingUtilities.invokeLater(() -> {
          lSpeed.setText(m.getOrDefault("speed","0.00"));
          lBat.setText(  m.getOrDefault("battery","0"));
          lTemp.setText( m.getOrDefault("temp","0.0"));
          lHead.setText( m.getOrDefault("heading","-"));
        });
      }
    }
    s.close();
  }
}
