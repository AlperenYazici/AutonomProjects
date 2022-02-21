# AutonomProjects
Autonom mülakat projeleri
Proje 1:
Nucleo-f302re geliştirme boardı üzerinde geliştirildi.
  
   Projenin genel yapısı uygulama katmanı; board katmanı , 
rtos katmanı ve uygulama katmanının board katmanına erişimi 
için bsp interface, rtos katmanına
erişimi için rtos interface bulunmasıdır.
Uygulamada 2 task bulunmaktadır. Task 1, taskLed taskı
Uygulamadaki ledin on-off sürelerinin işlendiği taskdır.
Task 2, taskUartEcho taskının görevi UART'dan beklediği
event gelirse çalışıp gelen mesajı karşı tarafa echolamaktır.
Ayrıca uygulamada birde uart receive kesmesi çalışmaktadır.
Burada gelen data enter karakterine kadar toplanıp,komut olarak
işlenmektedir.
   Projede uygulama katmanı UartCom,LedManager donanım ve rtos
katmanından IBSP ve IRTOS interfaceleri ile soyutlanarak loosely-coupled
bir programlama dolayısıyla modüler bir programlama hedeflenmiştir. Ayrıca
Uygulama katmanı arasında nesnelerin birbiri ile iletişimi interfaceler ile
soyutlanarak loosely-coupled ilkesine göre hareket edilmiştir. Farklı donanım
ve farklı rtos sistemlerine projenin geçirilmesinin uygulama katmanına etkisi
oldukça azaltılmış ve kolaylaştırılmıştır.
