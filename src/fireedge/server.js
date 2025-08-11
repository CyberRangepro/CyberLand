
const express = require('express');
const bodyParser = require('body-parser');
const xmlrpc = require('xmlrpc');
const path = require('path');
const helmet = require('helmet');
const compression = require('compression');
const os = require('os');

const app = express();
const port = process.env.PORT || 3000;
const xmlrpcClient = xmlrpc.createClient({ host: 'localhost', port: 8080, path: '/' });
// Middleware للسماح بطلبات CORS

app.use(helmet.xssFilter());
app.use(helmet.hidePoweredBy());
app.use(compression());
app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  res.header(
    'Access-Control-Allow-Headers',
    'Origin, X-Requested-With, Content-Type, Accept'
  );
  next();
});

// Middleware لتسجيل الطلبات
app.use((req, res, next) => {
  console.log(`${new Date().toISOString()} - ${req.method} ${req.url}`);
  next();
});

// serve static files
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

// API endpoint لإرسال بيانات استهلاك CPU و RAM
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
// صفحة الرئيسية
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'cyperland.html'));
});

// صفحة 404 مخصصة
app.use((req, res) => {
  res.status(404).sendFile(path.join(__dirname, 'public', '404.html'));
});

app.post('/api/xml-rpc', (req, res) => {
  const { method, params } = req.body;

  console.log(`[Node.js] استقبال طلب: ${method}`, params);

  // تنفيذ الطلب على سيرفر C++
  cppClient.methodCall(method, [params], (err, value) => {
    if (err) {
      console.error("[Node.js] خطأ في الاتصال بـ C++:", err);
      return res.json({ error: `فشل في الاتصال بالسيرفر: ${err.message}` });
    }

    console.log("[Node.js] الرد من C++:", value);
    res.json({ result: value });
  });
});

app.listen(port, () => {
  console.log(`الخادم يعمل على http://localhost:${port}`);
});
