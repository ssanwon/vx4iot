const listUl = document.querySelector('.list');
const lis = listUl.children;
const divList1 = document.querySelector('.listHolder');

function addLists(s) {
    const ul = divList1.querySelector('ul');
    const li = document.createElement('li');
    addLists_1(li, s);
    ul.appendChild(li);
}

function addLists_1(ul, s) {
    const span = document.createElement('span');
    span.textContent = s;
    span.setAttribute('class', 'listName')
    ul.appendChild(span);
}

function removeList() {
    while (listUl.hasChildNodes()) {
        listUl.removeChild(listUl.firstChild);
    }
}

function removeText(s) {
    for (var i = 0; i < lis.length; i++) {
        let a = listUl.getElementsByClassName("listName")[i].innerHTML;
        if (a == s) {
            listUl.removeChild(listUl.children[i]);
        }
    }
}