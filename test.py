g=3

def a1():
  a=5
  b=7
  print(g)

  def a2():
    global g
    c=9
    g=4
    print(g)
    def a3():
      nonlocal c
      c=3
      print(g)
      print(c)
    a3()
    
    print(c)
  a2()
a1()

