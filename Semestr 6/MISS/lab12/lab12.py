import random

import matplotlib
matplotlib.use("TkAgg")

import matplotlib.pyplot as plt
import matplotlib.animation as animation

STATE_COLORS = {
    "C": "red",
    "Z": "yellow",
    "ZD": "orange",
    "ZZ": "green",
}

class Person:
    def __init__(self):
        self.age = random.randint(0, 100)
        if self.age < 15 or self.age > 70:
            self.resilience = random.randint(0, 2)
        elif 40 <= self.age < 70:
            self.resilience = random.randint(4, 5)
        else:
            self.resilience = random.randint(7, 9)

        self.state = "ZZ"
        self.speed = random.randint(1, 3)
        self.direction = [random.choice([-1, 1]), random.choice([-1, 1])]
        self.x = random.randint(1, 100)
        self.y = random.randint(1, 100)
        self.days_sick = 0
        self.alive = True

    def move(self):
        self.x += self.direction[0] * self.speed
        self.y += self.direction[1] * self.speed
        if self.x <= 0 or self.x >= 100:
            self.direction[0] *= -1
        if self.y <= 0 or self.y >= 100:
            self.direction[1] *= -1

    def update_days_sick(self):
        self.days_sick += 1
        if self.state == "Z" and self.days_sick >= 2:
            self.state = "C"
            self.days_sick = 0
        elif self.state == "C" and self.days_sick >= 7:
            self.state = "ZD"
            self.days_sick = 0
        elif self.state == "ZD" and self.days_sick >= 5:
            self.state = "ZZ"
            self.days_sick = 0

    def affect_resilience(self):
        if self.state == "Z":
            self.resilience -= 0.1
        elif self.state == "C":
            self.resilience -= 0.5
        elif self.state == "ZD":
            self.resilience = min(10, self.resilience + 0.1)
        elif self.state == "ZZ":
            self.resilience = min(10, self.resilience + 0.05)

        if self.resilience <= 0:
            self.alive = False


def max_dist(a, b):
    return max(abs(a.x - b.x), abs(a.y - b.y))


def max_resilience_for_age(age):
    if age < 15 or age > 70:
        return 3
    elif 40 <= age < 70:
        return 6
    else:
        return 10


def interact(a, b):
    if max_dist(a, b) > 2:
        return

    pair = (a.state, b.state)

    if pair == ("ZZ", "Z") or pair == ("Z", "ZZ"):
        zz, z = (a, b) if a.state == "ZZ" else (b, a)
        if zz.resilience < 3:
            zz.state = "Z"

    elif pair == ("ZZ", "C") or pair == ("C", "ZZ"):
        zz, c = (a, b) if a.state == "ZZ" else (b, a)
        if zz.resilience < 6:
            zz.state = "Z"
        elif zz.resilience >= 6:
            zz.resilience -= 3

    elif pair == ("ZZ", "ZD") or pair == ("ZD", "ZZ"):
        zd, zz = (a, b) if a.state == "ZD" else (b, a)
        zd.resilience = min(10, zd.resilience + 1)

    elif pair == ("ZZ", "ZZ"):
        max_r = max(a.resilience, b.resilience)
        a.resilience = min(max_resilience_for_age(a.age), max_r)
        b.resilience = min(max_resilience_for_age(b.age), max_r)

    elif pair == ("C", "Z") or pair == ("Z", "C"):
        c, z = (a, b) if a.state == "C" else (b, a)
        if z.resilience < 6:
            z.state = "C"
            z.days_sick = 0
        c.days_sick = 0

    elif pair == ("C", "ZD") or pair == ("ZD", "C"):
        zd, c = (a, b) if a.state == "ZD" else (b, a)
        if zd.resilience < 6:
            zd.state = "Z"
            zd.days_sick = 0

    elif pair == ("C", "C"):
        min_r = min(a.resilience, b.resilience)
        a.resilience = min_r
        b.resilience = min_r
        a.days_sick = 0
        b.days_sick = 0

    elif pair == ("Z", "ZD") or pair == ("ZD", "Z"):
        zd, z = (a, b) if a.state == "ZD" else (b, a)
        zd.resilience -= 1

    elif pair == ("Z", "Z"):
        a.resilience -= 1
        b.resilience -= 1

    elif pair == ("ZD", "ZD"):
        pass


def animate_simulation(pop, days):
    fig, ax = plt.subplots()

    xs = [p.x for p in pop]
    ys = [p.y for p in pop]
    colors = [STATE_COLORS.get(p.state, "black") for p in pop]

    scat = ax.scatter(xs, ys, s=20, c=colors)
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)

    def update(frame):
        for person in pop:
            person.move()
            person.affect_resilience()
            person.update_days_sick()

        for i in range(len(pop)):
            for j in range(i + 1, len(pop)):
                if pop[i].alive and pop[j].alive:
                    interact(pop[i], pop[j])

        alive_people = [p for p in pop if p.alive]
        xs = [p.x for p in alive_people]
        ys = [p.y for p in alive_people]
        colors = [STATE_COLORS.get(p.state, "black") for p in alive_people]

        scat.set_offsets(list(zip(xs, ys)))
        scat.set_color(colors)
        ax.set_title(f"Day {frame + 1} — Alive: {len(alive_people)}")
        return scat,

    ani = animation.FuncAnimation(fig, update, frames=days, interval=300, repeat=False)
    plt.show(block=True)


def main():
    population = [Person() for _ in range(100)]
    for i in range(5):
        population[i].state = "Z"

    animate_simulation(population, 100)


if __name__ == "__main__":
    main()
