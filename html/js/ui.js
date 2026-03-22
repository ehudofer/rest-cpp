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


  if (!state.user) {
    app.innerHTML = `<div class="card login-card">
  <h1>Login</h1>

  <form id="login-form">
    <input
      type="text"
      id="username"
      placeholder="Username"
      autocomplete="username"
      required
    />

    <input
      type="password"
      id="password"
      placeholder="Password"
      autocomplete="current-password"
      required
    />

    <button type="submit">Sign in</button>
  </form>
</div>`;
    return;
  }

  app.innerHTML = `
    <h1>Hello ${state.user.name}</h1>
    <pre>${JSON.stringify(state.data, null, 2)}</pre>
  `;
}