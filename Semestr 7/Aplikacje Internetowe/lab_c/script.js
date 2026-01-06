document.getElementById("saveButton").addEventListener("click", function () {
    if (
        Notification.permission !== "granted" &&
        Notification.permission !== "denied"
    ) {
        Notification.requestPermission();
    }

    leafletImage(map, function (err, sourceCanvas) {
        const boardWidth = 600;
        const boardHeight = 300;

        const boardRows = 4;
        const boardCols = 4;

        const trayRows = 2;
        const trayCols = 8;

        const boardPieceWidth = boardWidth / boardCols;
        const boardPieceHeight = boardHeight / boardRows;

        const puzzleBoard = document.getElementById("puzzleBoard");
        puzzleBoard.innerHTML = "";
        puzzleBoard.style.display = "grid";
        puzzleBoard.style.gridTemplateRows = `repeat(${boardRows}, ${boardPieceHeight}px)`;
        puzzleBoard.style.gridTemplateColumns = `repeat(${boardCols}, ${boardPieceWidth}px)`;
        puzzleBoard.style.width = boardWidth + "px";
        puzzleBoard.style.height = boardHeight + "px";
        puzzleBoard.style.gap = "0px";

        const trayHeight = boardPieceHeight * trayRows;
        const trayWidth = boardPieceWidth * trayCols;
        const trayPieceWidth = trayWidth / trayCols;
        const trayPieceHeight = trayHeight / trayRows;

        let oldTray = document.getElementById("tray");
        if (oldTray) oldTray.remove();

        const tray = document.createElement("div");
        tray.id = "tray";
        tray.style.display = "grid";
        tray.style.gridTemplateRows = `repeat(${trayRows}, ${trayPieceHeight}px)`;
        tray.style.gridTemplateColumns = `repeat(${trayCols}, ${trayPieceWidth}px)`;
        tray.style.width = trayWidth + "px";
        tray.style.height = trayHeight + "px";
        tray.style.gap = "0px";
        tray.style.marginTop = "20px";
        tray.style.border = "1px solid black";
        document.body.appendChild(tray);

        const boardSlots = [];
        for (let i = 0; i < boardRows * boardCols; i++) {
            const slot = document.createElement("div");
            slot.dataset.correctPiece = i;
            slot.style.width = boardPieceWidth + "px";
            slot.style.height = boardPieceHeight + "px";
            slot.style.border = "1px dashed gray";
            slot.style.boxSizing = "border-box";
            slot.addEventListener("dragover", (e) => e.preventDefault());
            slot.addEventListener("drop", dropPiece);
            puzzleBoard.appendChild(slot);
            boardSlots.push(slot);
        }

        const traySlots = [];
        for (let i = 0; i < trayRows * trayCols; i++) {
            const slot = document.createElement("div");
            slot.style.width = trayPieceWidth + "px";
            slot.style.height = trayPieceHeight + "px";
            slot.style.border = "1px dashed gray";
            slot.style.boxSizing = "border-box";
            slot.addEventListener("dragover", (e) => e.preventDefault());
            slot.addEventListener("drop", dropPiece);
            tray.appendChild(slot);
            traySlots.push(slot);
        }

        const pieces = [];
        for (let y = 0; y < boardRows; y++) {
            for (let x = 0; x < boardCols; x++) {
                const piece = document.createElement("canvas");
                piece.width = boardPieceWidth;
                piece.height = boardPieceHeight;
                const ctx = piece.getContext("2d");
                ctx.drawImage(
                    sourceCanvas,
                    x * boardPieceWidth,
                    y * boardPieceHeight,
                    boardPieceWidth,
                    boardPieceHeight,
                    0,
                    0,
                    boardPieceWidth,
                    boardPieceHeight
                );
                piece.draggable = true;
                piece.dataset.correctIndex = pieces.length;
                piece.id = "piece_" + pieces.length;
                piece.addEventListener("dragstart", (e) => {
                    e.dataTransfer.setData("pieceId", piece.id);
                });
                pieces.push(piece);
            }
        }

        const shuffledSlots = [...traySlots].sort(() => Math.random() - 0.5);
        for (let i = 0; i < pieces.length; i++) {
            shuffledSlots[i].appendChild(pieces[i]);
        }

        function dropPiece(e) {
            e.preventDefault();
            const id = e.dataTransfer.getData("pieceId");
            const piece = document.getElementById(id);

            if (this.children.length === 0) {
                this.appendChild(piece);
            } else {
                return;
            }

            const allCorrect = boardSlots.every((slot) => {
                if (slot.children.length === 0) {
                    return false;
                }
                const child = slot.children[0];
                return (
                    parseInt(child.dataset.correctIndex) ===
                    parseInt(slot.dataset.correctPiece)
                );
            });

            if (allCorrect) {
                new Notification("Puzzle Completed!");
            }
        }
    });
});
