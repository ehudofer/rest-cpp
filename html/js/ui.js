export function render(state) {
  const app = document.getElementById('app');

//TODO: move to .js
  // Handle login form submission
  document.addEventListener('submit', async (e) => {
  if (e.target.id !== 'login-form') return;

  e.preventDefault();

  const username = document.getElementById('username').value;
  const password = document.getElementById('password').value;

  try {
    await login(username, password);
  } catch (err) {
    alert('Login failed');
  }
});

var login_username = '';
var login_password = '';

  if (!state.user) {
    app.innerHTML = `<div class="card login-card">
  <h1>Login</h1>

  <form id="login-form">
    <input
      type="text"
      id="username"
      placeholder="Username"
      autocomplete="username"
      value="${login_username}"
      required
    />

    <input
      type="password"
      id="password"
      placeholder="Password"
      autocomplete="current-password"
      value="${login_password}"
      required
    />

    <button type="submit">Sign in</button>
  </form>
</div>`;
document.getElementById('username').addEventListener('', e => login_username = e.target.value);
document.getElementById('password').addEventListener('input', e => login_password = e.target.value);
    return;
  }

  app.innerHTML = `
    <h1>Hello ${state.user.name}</h1>
    <p>Username: ${state.user.username}</p>
    <pre>${JSON.stringify(state.data, null, 2)}</pre>
  `;
}