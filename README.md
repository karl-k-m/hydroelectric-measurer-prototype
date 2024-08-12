<h1 align="center"> Hydroelectric Plant Water Measuring System Prototype</h1>
<h3 align="center"> Both a water level measuring system and an example of my impeccable creativity in the naming of my repos. </h3>

<h2 id="table-of-contents"> :book: Table of Contents</h2>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#why"> ➤ Why need?</a></li>
    <li><a href="#system"> ➤ The system</a></li>
    <li><a href="#future"> ➤ Future plans</a></li>
    <li><a href="#team"> ➤ The Team</a></li>
  </ol>
</details>

<hr>

<!-- TL;DR -->
<h2 id="why"> :pencil: Why need?</h2>
<p>
  The problem this project intends to solve is that of culling practices used by some power plants to improve productivity, which however negatively affects migratory fish.

  ![Untitled](https://github.com/user-attachments/assets/0be3ce88-6cb0-4227-a971-f83e67d8f6d4)

  Hydroelectric power station operators create artificial lakes or reservoirs using dams. This allows them to store up water and use it later to generate electricity at times when it is more beneficial to the power plant. However, this negatively affects migratory fish and the natural environment. To allow the fish to move, hydroelectric power stations in Estonia are subject to several requirements, including limitations on how much they can change the water level in a 24 hour period.  
  Specifically, Estonia limits this to 30cm per day. Compliance with these requirements is monitored by the Estonian Environmental Board.  
  Currently, the monitoring of these requirements is done either manually on-location or using cameras. These methods are both expensive and (in case of cameras) potentially unreliable. This is why we decided to design a kind of solid-state measurement device built specifically for this purpose.  
</p>

<!-- SYSTEM -->
<h2 id="system"> 💻 Our System</h2>
<p>
  Our device uses multiple electromagnetic water level sensors within a sealed tube to measure the water level. This approach has multiple benefits compared to alternative solutions:
  <ul>
    <li>It is not affected by water surface conditions or temperature (which could throw off pressure and IR sensors).</li>
    <li>Compared to mechanical switches (e.g. floating reed switches), the design is very low-maintenance, as there are no moving parts and the electronics used are very reliable.</li>
    <li>They are more difficult to tamper with compared to something like an optical sensor. This is because the sensors only react to water (or objects with a high water content).</li>
  </ul>
</p>

<p>
  To reiterate - this repository only contains information, specs and code of a very limited proof-of-concept. As such, what you see here is not at all representative of the current state of the project. This is how the prototype worked:  
  
  ![image](https://github.com/user-attachments/assets/c08f4764-d092-4a63-b44f-3c66e77fc652)  

  The sensor contained an ESP32 module which was connected to a smartphone's wifi hotspot. The ESP32 periodically sends data from the device to a centralized MySQL server which stores the data for each node, along with timestamps. Our solution also included a Grafana dashboard for easy visualization of the data. The entire system was powered via a car battery.

  
</p>

<!-- SYSTEM -->
<h2 id="future"> 👽 Future</h2>
<p>
  As the project is ongoing, new developments will still remain a mystery for now. However, I will specify some of the more obvious updates:
  <ul>
    <li>The prototype used an ESP32 connected to a phone's hotspot for internet access. This is obviously not practical in production. An updated design uses a GSM module. A GSM module is essentially a device that allows you to connect to a GSM (2G) cellular network using a SIM card. To simplify a bit, this is the same system that companies like Bolt use for their rental scooters.</li>
    <li>The prototype was powered by a car battery. This is also obviously unpractical. A production system would use a battery contained within the device itself, and use a device which takes far less power than an ESP. This would allow it to run for a *very* long time without recharging.</li>
  </ul>
</p>

<!-- TEAM -->
<h2 id="team"> 🧑‍🤝‍🧑 The Team</h2>
<p>
  This project was created by myself and three others whose identities I will not reveal for the sake of their privacy. However, they are brilliant and deserve credit!  
  
  ![Untitled](https://github.com/user-attachments/assets/c1b5a13c-eefd-471f-9b3a-ff9bb9e25033)

</p>
