
import java.io.*;
import java.net.Socket;

public class S {
    public static void main(String[] args) {
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    ServerSocket serverSocket = new ServerSocket(8080);
//                    System.out.println("服务器启动，等待客户端连接...");
//                    Socket socket = serverSocket.accept();
//                    System.out.println("客户端连接成功");
//                    BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//                    String line;
//                    while ((line = reader.readLine()) != null) {
//                        System.out.println("接收到数据: " + line);
//                    }
//                    reader.close();
//                    socket.close();
//                    serverSocket.close();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Socket socket = new Socket("localhost", 5555);
                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
                    String line;
                    while ((line = reader.readLine()) != null) {
                        writer.write(line);
                        if (line == "Close") {
                            continue;
                        }
                        if (line == "Cont") {
                            continue;
                        }
                        writer.newLine();
                        writer.flush();
                    }
                    writer.close();
                    reader.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
