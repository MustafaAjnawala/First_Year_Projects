var form = document.getElementById("to-do-form");
var list = document.getElementById("to-do-list");

// Add a submit event listener to the form
form.addEventListener("submit", function(event) {
  event.preventDefault();//prevents frm reloading the page on submit press
  
  // Get the task input value
  var task = document.getElementById("task").value;
  // Check if the task input is not empty
  if (task !== "") {
    // Create a new list item
    var li = document.createElement("li");
    li.innerHTML = task + '<a href="#">X</a>';//adding an inner element to the list fpr the ddelete button

    // Append the list item to the list
    list.appendChild(li);

    // Clear the task input
    document.getElementById("task").value = "";
  }
});

// Add a click event listener to the list
list.addEventListener("click", function(event) {
  // Check if the clicked element is a delete link(in this case an anchor tag)
  if (event.target.tagName === "A") 
    {
    // Get the parent list item
    var li = event.target.parentNode;

    // Remove the parent list item from the list
    list.removeChild(li);
  }
});