# Game Instance Services
Service is singleton with GameInstance's lifetime. <br>
They can be implemented by C++ and Blueprints out of box easily. <br>
<br>
![SaveLoadServiceShowcase](Docs/SaveLoadServiceShowcase.png)

<br>
Services useful to separate logic from GameInstance to their own classes.
<br>

Let's say you have SaveLoad System, Auth Logic and maybe some statistic methods and all this implemented at GameInstance class and it's grown over and over.<br>
Separate their to own classes is a good practice. <br>
You can choose GameInstanceSubsystem, and usualy it's enought.<br>
And Game Instance Services is your choice if you want:<br>
1. Easialy implement service as Blueprint. <br>
2. Make relationships between services. <br>
<br>

# Game Instance Services lifetime
Service initialized when created.<br>
Because service is singleton it's created once on first access to it (GetService func).<br>
If you want to start service when GameInstance started - just add service class to "Startup Services" at "Project Settings" -> "Services Subsystem Settings"<br>
Use PostStartup func if your services depends on each other - it's called once whan all "Startup Services" are created and initialized.<br>