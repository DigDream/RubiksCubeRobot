private Runnable runnable = new Runnable() {
        public void run() {
            try {
                socket = new Socket("192.168.8.1", 2001);
                // bufferedReader = new BufferedReader(new
                // InputStreamReader(socket.getInputStream()));
                printWriter = new PrintWriter(socket.getOutputStream(), true);
                OutputStream os = socket.getOutputStream();
                printWriter = new PrintWriter(os, true);
            } catch (Exception e) {
//				Tools.tips(Ctr.this, "Á¬œÓŽíÎó,ÇëŒì²éÍøÂç");
                return;
            }
        }
    };


    /**
     * @param event
     */
    private void touchHandle(MotionEvent event, String orderStr, String tips) {
        int action = event.getAction();
        switch (action) {
            case MotionEvent.ACTION_DOWN:
                ctrOrder(orderStr, tips);
                break;
            case MotionEvent.ACTION_UP:
                ctrOrder("e", "Í£");
                break;
            default:
                break;
        }
    }

    private void ctrOrder(String orderStr, String tips) {
        printWriter.print(orderStr);
        printWriter.flush();
        // if(tips != null && !"".equals(tips)){
        // Tools.tips(Ctr.this, tips);
        // }

    }

    public void onDestroy() {
        super.onDestroy();
        if (isConnect) {
            isConnect = false;
            try {
                if (socket != null) {
                    socket.close();
                    socket = null;
                    printWriter.close();
                    printWriter = null;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            thread.interrupt();
        }

    }

    touchHandle(event, "d", "ÓÒ");