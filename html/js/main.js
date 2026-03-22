import { api, setToken } from './api.js';
import { state } from './state.js';
import { render } from './ui.js';

async function load() {
    if (!state.user) {
        render(state);
        return;
    }
  state.data = await api('/api/data');
  render(state);
}

// async function login() {
//   const res = await api('/api/login', {
//     method: 'POST',
//     body: JSON.stringify({ user: 'a', pass: 'b' })
//   });

//   setToken(res.token);
//   state.user = res.user;
//   load();
// }

// render(state);
// document.addEventListener('click', e => {
//   if (e.target.id === 'login') login();
// });

setInterval(load, 5000);
