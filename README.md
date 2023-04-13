
# **Stop Watch Using AVR Microcontroller**

a stopwatch application implemented on an AVR microcontroller. The application uses a timer to generate an interrupt every second and updates the displayed stopwatch value accordingly. The application also uses external interrupts to reset, pause and resume the stopwatch.

The stopwatch is displayed using a 7-segment display connected to PORTA and PORTC of the microcontroller. The first 6 bits of PORTA are used to control the segments of the leftmost digit, and the next 4 bits of PORTC are used to control the segments of the other three digits.

## **Table of Contents**

- [Proteus](#Proteus)
- [Driveers](#Driveers)
- [conclusion](#conclusion)
- [Contact](#Contact)
- [Contributing](#contributing)


## **Proteus**

![simulation](https://github.com/Esmtra/Stop_Watch_app-MT_embedded_diploma/blob/main/img/simulation.png "simulation")

## **Driveers**
- The application uses three external interrupts, INT0, INT1 and INT2, to perform different functions on the stopwatch. INT0 is used to reset the stopwatch, INT1 is used to pause the stopwatch, and INT2 is used to resume the stopwatch.

- The application uses Timer1 in CTC (Clear Timer on Compare) mode to generate interrupts every second. Timer1 is configured to use a clock frequency of F_CPU/1024, where F_CPU is the frequency of the system clock. The timer compare value is set to 1000, which means that an interrupt is generated every 1000 timer ticks (i.e., every 1 second).


## **conclusion**
The stopwatch application implemented on an AVR microcontroller uses a timer and external interrupts to control the stopwatch display on a 7-segment display connected to PORTA and PORTC. It allows for reset, pause, and resume functions.

## **Contact**

- **[Eslam S Rady](mailto:Eselmtrawy@gmail.com)** - Email address
- **[GitHub](https://github.com/Esmtra)** - GitHub profile link
- **[LinkedIn](https://www.linkedin.com/in/eslam-mtra-1714201b7/)** - LinkedIn profile link


## **Contribution**
This is a basic stopwatch app and may require further development to be more robust and scalable. Contributions are welcome, and issues can be reported through the project's Github issue tracker.
