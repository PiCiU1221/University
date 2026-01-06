class Todo {
    constructor(listElement) {
        this.taskList = listElement;
        this.tasks = JSON.parse(localStorage.getItem("tasks")) || [];
        this.term = "";
        this.draw();
    }

    saveTasks() {
        localStorage.setItem("tasks", JSON.stringify(this.tasks));
    }

    addTask(text, date) {
        this.tasks.push({ text, date });
        this.saveTasks();
        this.draw();
    }

    deleteTask(index) {
        this.tasks.splice(index, 1);
        this.saveTasks();
        this.draw();
    }

    editTask(index, newText, newDate) {
        this.tasks[index].text = newText;
        this.tasks[index].date = newDate;
        this.saveTasks();
        this.draw();
    }

    setSearchTerm(term) {
        this.term = term.toLowerCase();
        this.draw();
    }

    get filteredTasks() {
        if (!this.term || this.term.length < 2) return this.tasks;
        return this.tasks.filter((task) =>
            task.text.toLowerCase().includes(this.term)
        );
    }

    draw() {
        this.taskList.innerHTML = "";
        this.filteredTasks.forEach((task, index) => {
            const li = this.createTaskElement(task, index);
            this.taskList.appendChild(li);
        });
    }

    createTaskElement(task, index) {
        const li = document.createElement("li");

        li.append(
            this.createTaskText(task.text),
            this.createTaskDate(task.date),
            this.createEditButton(task, index),
            this.createDeleteButton(index)
        );

        return li;
    }

    createTaskText(text) {
        const span = document.createElement("span");
        span.className = "task-text";

        if (this.term.length >= 2) {
            const regex = new RegExp(`(${this.term})`, "gi");
            span.innerHTML = text.replace(regex, "<mark>$1</mark>");
        } else {
            span.textContent = text;
        }

        return span;
    }

    createTaskDate(date) {
        const span = document.createElement("span");
        span.className = "task-date";
        span.textContent = date;
        return span;
    }

    createDeleteButton(index) {
        const btn = document.createElement("button");
        btn.className = "delete-btn";
        btn.textContent = "Delete";
        btn.addEventListener("click", () => this.deleteTask(index));
        return btn;
    }

    createEditButton(task, index) {
        const btn = document.createElement("button");
        btn.className = "edit-btn";
        btn.textContent = "Edit";

        btn.addEventListener("click", () =>
            this.startEditing(task, index, btn)
        );
        return btn;
    }

    startEditing(task, index, editBtn) {
        const li = editBtn.parentElement;
        li.classList.add("editing");

        const wrapperInputs = document.createElement("div");
        wrapperInputs.className = "edit-input-date-wrapper";

        const textInput = document.createElement("input");
        textInput.type = "text";
        textInput.value = task.text;
        textInput.className = "edit-input";

        const dateInput = document.createElement("input");
        dateInput.type = "date";
        dateInput.value = task.date;
        dateInput.className = "edit-date";

        wrapperInputs.append(textInput, dateInput);

        const wrapperButtons = document.createElement("div");
        wrapperButtons.className = "edit-buttons-wrapper";

        const acceptBtn = document.createElement("button");
        acceptBtn.className = "accept-btn";
        acceptBtn.textContent = "Accept";
        acceptBtn.addEventListener("click", () => {
            const newText = textInput.value.trim();
            const newDate = dateInput.value;

            if (newText.length < 3 || newText.length > 255) {
                alert("Task name must be between 3 and 255 characters.");
                return;
            }

            if (
                newDate &&
                new Date(newDate) < new Date().setHours(0, 0, 0, 0)
            ) {
                alert("Date must be today or in the future.");
                return;
            }

            this.editTask(index, newText, newDate);
        });

        const cancelBtn = document.createElement("button");
        cancelBtn.className = "cancel-btn";
        cancelBtn.textContent = "Cancel";
        cancelBtn.addEventListener("click", () => this.draw());

        wrapperButtons.append(acceptBtn, cancelBtn);

        li.innerHTML = "";
        li.append(wrapperInputs, wrapperButtons);
    }
}

const taskListElement = document.getElementById("taskList");
const todo = new Todo(taskListElement);

document.getElementById("addTask").addEventListener("click", () => {
    const taskText = document.getElementById("newTask").value.trim();
    const taskDate = document.getElementById("newDate").value;

    if (taskText.length < 3 || taskText.length > 255) {
        alert("Task name must be between 3 and 255 characters.");
        return;
    }

    if (taskDate && new Date(taskDate) < new Date().setHours(0, 0, 0, 0)) {
        alert("Date must be today or in the future.");
        return;
    }

    todo.addTask(taskText, taskDate);
    document.getElementById("newTask").value = "";
    document.getElementById("newDate").value = "";
});

document.getElementById("search").addEventListener("input", (e) => {
    todo.setSearchTerm(e.target.value);
});
