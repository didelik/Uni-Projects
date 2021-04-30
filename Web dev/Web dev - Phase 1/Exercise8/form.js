const password = document.getElementById("password")
const confPassword = document.getElementById("confPassword")
const form = document.getElementById("testing")


form.style.backgroundColor = 'red'

form.addEventListener('submit',(e) =>){
  let messages = []

  if(password.value != confPassword.value){
    messages.push('Passwords do not match')
  }

  if(password.value.length <= 6){
    messages.push('Weak password.Few characters')
  }


  if(messages.length > 0){
    e.preventDefault()
    errorElement.innerText = messages.join(', ')
  }


})
