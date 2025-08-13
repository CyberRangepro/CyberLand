const express = require('express');
const xmlrpc = require('xmlrpc');
const path = require('path');
const helmet = require('helmet');
const compression = require('compression');
const os = require('os');

const app = express();
const port = process.env.PORT || 3000;

// إنشاء عميل XML-RPC
const xmlrpcClient = xmlrpc.createClient({ host: 'localhost', port: 8080, path: '/' });

// Middleware
app.use(helmet.xssFilter());
app.use(helmet.hidePoweredBy());
app.use(express.json());
app.use(compression());

// تسجيل الطلبات
app.use((req, res, next) => {
  console.log(`${new Date().toISOString()} - ${req.method} ${req.url}`);
  next();
});

// CORS
app.use((req, res, next) => {
  res.set('Access-Control-Allow-Origin', '*');
  res.set('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
  next();
});

// ✅ 1. مسار XML-RPC أولاً (قبل static)
app.post('/xmlrpc', (req, res) => {
  const { method, params } = req.body;

  if (!method) {
    return res.status(400).json({ error: 'Missing method' });
  }

  console.log(`[Node.js] استقبال طلب: ${method}`, params);

  // استخدام xmlrpcClient الصحيح، و params بدون [] إضافية
 xmlrpcClient.methodCall(method, Array.isArray(params) ? params : [params], (err, value) => {
    if (err) {
      console.error("[Node.js] خطأ في الاتصال بـ C++:", err);
      return res.status(500).json({ error: err.message });
    }

    console.log("[Node.js] الرد من C++:", value);
    res.json({ result: value });
  });
});

// ✅ 2. الملفات الثابتة
app.use(
  express.static(path.join(__dirname, 'public'), {
    maxAge: '30d',
    setHeaders: (res, filePath) => {
      res.set('X-Content-Type-Options', 'nosniff');
      res.set('X-Frame-Options', 'DENY');
      res.set('X-XSS-Protection', '1; mode=block');
      res.set(
        'Content-Security-Policy',
        "default-src 'self'; script-src 'self' 'unsafe-inline' https://cdn.jsdelivr.net; style-src 'self' 'unsafe-inline' https://cdn.jsdelivr.net; font-src 'self' https://cdnjs.cloudflare.com"
      );
    }
  })
);

// ✅ 3. API أخرى
app.get('/api/stats', (req, res) => {
  const totalMem = os.totalmem();
  const freeMem = os.freemem();
  const usedMem = totalMem - freeMem;
  const usedMemPercent = ((usedMem / totalMem) * 100).toFixed(2);
  const cpuLoad = ((os.loadavg()[0] / os.cpus().length) * 100).toFixed(2);

  res.json({
    cpuLoadPercent: cpuLoad,
    ramUsagePercent: usedMemPercent,
    totalMemMB: (totalMem / 1024 / 1024).toFixed(2),
    usedMemMB: (usedMem / 1024 / 1024).toFixed(2),
    freeMemMB: (freeMem / 1024 / 1024).toFixed(2)
  });
});

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'cyperland.html'));
});

// ✅ 4. صفحة 404 في النهاية
app.use((req, res) => {
  res.status(404).sendFile(path.join(__dirname, 'public', '404.html'));
});

app.listen(port, () => {
  console.log(`الخادم يعمل على http://localhost:${port}`);
});