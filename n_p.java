import java.io.*;
import java.util.*;

public class n_p{
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    int i = Integer.parseInt(st.nextToken());
    int j = Integer.parseInt(st.nextToken());

    System.out.print(i + " " + j + " ");

    int count = 0;
    for(; i<=j; i++){
      int n = i;
      int tmp = 0;
      while(n != 1){
        tmp++;
        if(n%2 == 0){
          n = n/2;
        }else{
          n = 3*n + 1;
        }
      }
      count = Math.max(count, tmp);
    }
    
    System.out.println(count+1);
  }
}