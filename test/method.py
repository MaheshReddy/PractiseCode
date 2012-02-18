class temp:
    def __getattribute__(self,x):
        print "Accessed get attr ",x
        return 0
    def __setattribute__(self,x,y):
        print "Accessed set attr",y
class Foo(object):
    def __init__(self):
        self.id=1
        self.id2=temp()
    def __getattribute__(self,x):
        pass
        print "got ",x
        print type(self)
        print self.__dict__[x]
        #return self.__dict__[x]
    def __setattribute__(self,x,y):
        print "set ",x

def fun1(obj):
    print "i got this object",obj
Foo.fun=fun1


f=Foo()
print f.a
#f.fun()
#Foo.fun(f)
#fun1(f)
#dir(fun1)
#print Foo.__dict__
#for i in Foo.__dict__:
#    print i,type(Foo.__dict__[i]),Foo.__dict__[i]
#
#print "dasdasdasdasdasdasdasdadasdasdas"
#f.fun
#print type(f.fun.__dict__),(f.fun.__dict__)
#print dir(f)
#f.temp="dsad"
#print (f.__dict__)
#print f.id2
#for i in f.__dict__:
 #   print i,type(f.__dict__[i]),f.__dict__[i]
#print type(f).__dict__
#type(f).__dict__['temp'].__get__(f, type(f))
