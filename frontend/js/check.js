const apiUrl = 'mongodb+srv://team:<Global123>@cluster0.aucjgtn.mongodb.net/?retryWrites=true&w=majority';

function fetchData() {
  axios.get(apiUrl,{timeout:5000})
    .then(response => {
      const data = response.data;
      displayData(data);
    })
    .catch(error => {
      console.error('Error fetching data:', error);
    });
} 
function displayData(data) {
    console.log(data);
    const dataOutput = document.getElementById('data-output');
    dataOutput.innerHTML = '';
  
    const tr = document.createElement('tr');
    tr.innerHTML = `
    <td>${ 3.44|| 'N/A'}</td>
    <td>${8.06 || 'N/A'}</td>
    <td>${85|| 'N/A'}</td>
    <td>${96.112 || 'N/A'}</td>
  `;
    dataOutput.appendChild(tr)
  }
  window.onload = function () {
    setTimeout(function () {
        fetchData();
      }, 5000);
  };
  
